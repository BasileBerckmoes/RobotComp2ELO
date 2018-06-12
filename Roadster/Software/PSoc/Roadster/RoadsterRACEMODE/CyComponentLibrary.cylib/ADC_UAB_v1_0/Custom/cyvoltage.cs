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
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace ADC_UAB_v1_0
{
    /// <summary>
    /// Placeholder class.
    /// 
    /// Delete if we don't end up needing to query design voltages.
    /// </summary>
    public static class CyVoltage
    {
        public static double GetDesignVddaValue(ICyInstQuery_v1 instQuery)
        {
            double vdda_V;

            try
            {
                vdda_V = instQuery.VoltageQuery.VDDA;
            }
            catch
            {
                vdda_V = 0.0;
            }

            return vdda_V;
        }

        public static CyEBandgapGain GetDesignBandgapGain(ICyInstQuery_v1 instQuery)
        {
            double bandgap_V = 1.20;
            try
            {
                bandgap_V = instQuery.VoltageQuery.BandgapReference;
            }
            catch
            {
                bandgap_V = 1.20;   // PSoC 4B-S0 bandgap with gain 1
            }

            // PSoC 4B-S0 bandgap is 1.20V or 2.40V.
            var gain = (bandgap_V < 2.0) ? CyEBandgapGain.One : CyEBandgapGain.Two;

            return gain;
        }
    }
}

//[] END OF FILE
