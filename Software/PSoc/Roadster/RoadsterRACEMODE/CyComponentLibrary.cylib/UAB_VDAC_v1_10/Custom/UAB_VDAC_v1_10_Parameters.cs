/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace UAB_VDAC_v1_10
{
    // Component parameter names
    public class CyParamNames
    {
        // Begin component parameter names
        public const string DAC_GAIN = "DacGain";
        public const string DAC_SELECT = "DacSelect";
        public const string EXT_MODBIT = "ExtModBit";
        public const string VREF_SOURCE = "VrefSource";
        public const string VREF_V = "VrefVolts";
        public const string VAGND_SOURCE = "VagndSource";
        public const string VAGND_V = "VagndVolts";
        public const string EXT_FEEDBACK = "ExtFeedback";
        public const string EXT_STROBE = "ExtStrobe";
        public const string USER_REF_CLK_RATE = "UserRefClkRate";
        public const string USER_REF_CLK_RATE_EN = "UserRefClkRateEn";
        public const string DEFAULT_OUT_V = "DefaultOutVolts";
        public const string DEFAULT_OUT_CODE = "DefaultOutCode";
        // End component parameter names
    }

    // Subcomponent names
    public class CySubComponentNames
    {
        public const string UAB_HALF = "UAB";
        public const string CTB_HALF = "CTB";
        public const string CLOCK = "internalClock";
        public const string OR_GATE_CLOCK = "clockApiWorkaround_OrGate";
    }

    public class CyTerminalNames
    {
        public const string CLOCK_TERM = "clk";
    }
    // Begin custom component parameter code
    public delegate void SideEffectHandler();

    public enum DacFormatType
    {
        MODE_2CMP = 0,
        MODE_SGNMAG = 1
    }

    public enum DacVinSource
    {
        SOURCE_INTERNAL = 0,
        SOURCE_EXTERNAL = 1
    }
    // End custom component parameter code

    public class CyParameters
    {
        private readonly ICyInstEdit_v1 m_edit;
        private readonly ICyInstQuery_v1 m_query;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        public CyUAB_VDAC_v1_10Control m_control;
        public event SideEffectHandler m_sideEffects;
        public double Chip_Max_V = 5.0;
        public double Chip_Min_V = 0.0;
        
        #region parameter variables
        private CyParamWrapper<double> m_defaultOut_v ;
        private CyParamWrapper<UInt16> m_defaultOut_code;
        public CyEnumWrapper<DacFormatType> m_dacMode;
        private CyParamWrapper<Int16> m_dacGain;

        public CyEnumWrapper<DacVinSource> m_vrefSrc;
        private CyParamWrapper<double> m_vref_v;

        public CyEnumWrapper<DacVinSource> m_vagndSrc;
        private CyParamWrapper<double> m_vagnd_v;
        
        private CyParamWrapper<bool> m_extStrobe;
        private CyParamWrapper<bool> m_extOutputFeedback;
        private CyParamWrapper<bool> m_extModBit;
        
        private CyParamWrapper<bool>   m_userRefClkRateEn;
        private CyParamWrapper<double> m_userRefClkRate_kHz;
        #endregion parameter variables

        #region parameter helper variables
        private double m_SignMagMaxOutVoltage;
        private double m_SignMagMinOutVoltage;
        private double m_TwosCompMaxOutVoltage;
        private double m_TwosCompMinOutVoltage;
        private double m_MaxOutVoltage;
        private double m_MinOutVoltage;
        #endregion parameter helper variables

        #region parameter properties
        // Begin component parameter properties
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_query; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        public float DefaultOutVolt
        {
            get { return (float)m_defaultOut_v.Value; }
            set
            {
                m_defaultOut_v.Value = value;
            }
        }
        public int DefaultOutCode
        {
            /* These use special translation functions, since the number format
             is different for certain DAC modes. */
            get
            {
                if (m_dacMode.Display == m_dacMode.ValueToDisplay(DacFormatType.MODE_SGNMAG))
                {
                    return SignMag13b2TwosComp(m_defaultOut_code.Value);
                }
                else
                {
                    return m_defaultOut_code.Value;
                }
            }
            set
            {
                if (m_dacMode.Display == m_dacMode.ValueToDisplay(DacFormatType.MODE_SGNMAG))
                {
                    m_defaultOut_code.Value = (UInt16)TwosComp2SignMag13b(value);
                }
                else
                {
                    m_defaultOut_code.Value = (UInt16)value;
                }
                if (m_edit != null)
                {
                    OnSideEffects(); /* Redraw xfer diagram */
                }
            }
        }
        
        public Int16 DacGain
        {
            get { return m_dacGain.Value; }
            set
            {
                m_dacGain.Value = value;
                if (m_edit != null)
                {
                    RecalculateVoltageClips();
                }
                OnSideEffects();
            }
        }
        public double VrefVolts
        {
            get { return m_vref_v.Value; }
            set
            {
                m_vref_v.Value = value;
                if (m_edit != null)
                {
                    RecalculateVoltageClips();
                    OnSideEffects(); /* Redraw xfer diagram */
                }
            }
        }
        public double VagndVolts
        {
            get { return m_vagnd_v.Value; }
            set
            {
                m_vagnd_v.Value = value;
                if (m_edit != null)
                {
                    RecalculateVoltageClips();
                    OnSideEffects();
                }
            }
        }

        public bool StrobeIsExternal
        {
            get { return m_extStrobe.Value; }
            set
            {
                m_extStrobe.Value = value;
            }
        }

        public bool ModbitIsExternal
        {
            get { return m_extModBit.Value; }
            set
            {
                m_extModBit.Value = value;
            }
        }

        public bool BufferIsFeedback
        {
            get { return m_extOutputFeedback.Value; }
            set
            {
                m_extOutputFeedback.Value = value;
            }
        }

        public bool ClockIsExternal
        {
            get { return m_userRefClkRateEn.Value; }
            set
            {
                m_userRefClkRateEn.Value = value;
            }
        }

        public double UserRefClkRate_kHz
        {
            get { return m_userRefClkRate_kHz.Value; }
            set
            {
                m_userRefClkRate_kHz.Value = value;
                if (m_edit != null)
                {
                    OnSideEffects();
                }
            }
        }
        // End component parameter properties
        #endregion parameter properties
        #region parameter helper properties


        public double MaximumOutputVoltage
        {
            get { return m_MaxOutVoltage; }
            set
            {
                m_MaxOutVoltage = value;
            }
        }

        public double MinimumOutputVoltage
        {
            get { return m_MinOutVoltage; }
            set
            {
                m_MinOutVoltage = value;
            }
        }

        public double SignMagMaximumOutVoltage
        {
            get { return m_SignMagMaxOutVoltage; }
            set
            {
                m_SignMagMaxOutVoltage = value;
            }
        }

        public double SignMagMinimumOutVoltage
        {
            get { return m_SignMagMinOutVoltage; }
            set
            {
                m_SignMagMinOutVoltage = value;
            }
        }
        
        public double TwosCompMaximumOutVoltage
        {
            get { return m_TwosCompMaxOutVoltage; }
            set
            {
                m_TwosCompMaxOutVoltage = value;
            }
        }

        public double TwosCompMinimumOutVoltage
        {
            get { return m_TwosCompMinOutVoltage; }
            set
            {
                m_TwosCompMinOutVoltage = value;
            }
        }

        public double Range_VrefMin { get; set; }
        public double Range_VrefMax { get; set; }
        public double Range_VagndMin { get; set; }
        public double Range_VagndMax { get; set; }
        public double Range_FreqMin { get; set; }
        public double Range_FreqMax { get; set; }
        #endregion parameter helper properties

        /// <summary>
        /// This is the model of a Model-view-controller pattern.
        /// </summary>
        /// <param name="instQuery"></param>
        /// <param name="instEdit"></param>
        /// <param name="termQuery"></param>
        public CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            this.m_query = instQuery;
            this.m_edit = instEdit;
            this.m_termQuery = termQuery;
            Chip_Max_V = instQuery.VoltageQuery.VDDA;
            Range_VagndMax = Chip_Max_V - 0.5;
            Range_VagndMin = 0.5;
            Range_VrefMax = Chip_Max_V - 0.5;
            Range_VrefMin = 0.5;
            Range_FreqMin = 100;
            Range_FreqMax = 2000;
            m_defaultOut_v = new CyParamWrapper<double>(m_edit, CyParamNames.DEFAULT_OUT_V);
            m_defaultOut_code = new CyParamWrapper<UInt16>(m_edit, CyParamNames.DEFAULT_OUT_CODE);
            m_dacMode = new CyEnumWrapper<DacFormatType>(m_edit, CyParamNames.DAC_SELECT);
            m_dacGain = new CyParamWrapper<Int16>(m_edit, CyParamNames.DAC_GAIN);
            m_vrefSrc = new CyEnumWrapper<DacVinSource>(m_edit, CyParamNames.VREF_SOURCE);
            m_vref_v = new CyParamWrapper<double>(m_edit, CyParamNames.VREF_V);
            m_vagndSrc = new CyEnumWrapper<DacVinSource>(m_edit, CyParamNames.VAGND_SOURCE);
            m_vagnd_v = new CyParamWrapper<double>(m_edit, CyParamNames.VAGND_V);
            m_extStrobe = new CyParamWrapper<bool>(m_edit, CyParamNames.EXT_STROBE);
            m_extOutputFeedback = new CyParamWrapper<bool>(m_edit, CyParamNames.EXT_FEEDBACK);
            m_extModBit = new CyParamWrapper<bool>(m_edit, CyParamNames.EXT_MODBIT);
            m_userRefClkRateEn = new CyParamWrapper<bool>(m_edit, CyParamNames.USER_REF_CLK_RATE_EN);
            m_userRefClkRate_kHz = new CyParamWrapper<double>(m_edit, CyParamNames.USER_REF_CLK_RATE);

            Console.WriteLine(Convert.ToString(this.DefaultOutVolt));

            RecalculateVoltageClips(); 
        }

        protected void OnSideEffects()
        {
            if (m_sideEffects != null)
            {
                m_sideEffects();
            }
        }
        
        /// <summary>
        /// When options change, the maximum output voltage for each mode changes.
        /// This recalculates all of them (for each output mode) and sets the
        /// "global" variables MaximumVoltage & MinimumVoltage.
        /// </summary>
        public void RecalculateVoltageClips()
        {
            //UnsignedMaximumVoltage = Math.Min(Chip_Max_V, VrefVolts * (4.095 / 4.096));
            //UnsignedMinimumVoltage = 0.0;
            
            TwosCompMaximumOutVoltage = Math.Min(Chip_Max_V, VagndVolts + DacGain * VrefVolts * (4.095/4.096));
            TwosCompMinimumOutVoltage = Math.Max(Chip_Min_V, VagndVolts - DacGain * VrefVolts);

            SignMagMaximumOutVoltage = Math.Min(Chip_Max_V, VagndVolts + DacGain * VrefVolts * (4.095 / 4.096));
            SignMagMinimumOutVoltage = Math.Max(Chip_Min_V, VagndVolts - DacGain * VrefVolts * (4.095 / 4.096));

            
            if (m_dacMode.Value == DacFormatType.MODE_SGNMAG)
            {
                MaximumOutputVoltage = SignMagMaximumOutVoltage;
                MinimumOutputVoltage = SignMagMinimumOutVoltage;
            }/* else must be 2's comp mode... */
            else
            {
                MaximumOutputVoltage = TwosCompMaximumOutVoltage;
                MinimumOutputVoltage = TwosCompMinimumOutVoltage;
            }
            return;
        }

        /// <summary>
        /// Converts a 13 bit sign + magnitude encoded number to a two's complement
        /// encoded number.
        /// </summary>
        /// <param name="SignMagNum">Assumed that bit 13 is sign bit, bits[12:0] are magnitude.</param>
        /// <returns></returns>
        public int SignMag13b2TwosComp(int SignMagNum)
        {
            if ((SignMagNum & 0x00001000) > 0)
            {
                SignMagNum = (~(SignMagNum & 0x00000FFF) + 1) | 0x8000000;
            }
            return SignMagNum;
        }
        /// <summary>
        /// Converts a two's complement encoded number to a sign + magnitude
        /// encoded number.
        /// </summary>
        /// <param name="TwosCompNum">Assumed to be 13 bit. (Sign extended to 32 bit is okay)</param>
        /// <returns></returns>
        public int TwosComp2SignMag13b(int TwosCompNum)
        {
            return TwosCompNum >= 0 ? TwosCompNum : 0x00001000 | (-1 * TwosCompNum);
        }

    }
}
