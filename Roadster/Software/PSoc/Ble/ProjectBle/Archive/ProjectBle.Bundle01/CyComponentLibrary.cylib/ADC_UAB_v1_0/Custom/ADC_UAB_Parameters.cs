using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace ADC_UAB_v1_0
{
    // Component parameter names
    public class CyParamNames
    {
        // Begin component parameter names
        public const string ENDEDNESS = "Endedness";
        public const string V_RANGE = "VRange";
        public const string VREF_SOURCE = "VrefSource";
        public const string VREF_TAP = "VrefTap";
        public const string SHOW_SOC = "ShowSoc";
        public const string OSR = "OSR";
        // End component parameter names
    }

    #region Enums

    public enum CyEInputEndedness
    {
        SingleEnded = 0,
        Differential = 1,
    }

    public enum CyEGain
    {
        DoubleVref = 0,
        OneVref = 1,
        HalfVref = 2,
        FourthVref = 3,
        EighthVref = 4,
    }

    public enum CyEBandgapGain
    {
        One = 1,
        Two = 2,
    }

    public enum CyEVrefSource
    {
        Bandgap = 0,
        Vdda = 1,
    }

    public class CyVrefGainPair
    {
        public CyVrefGainPair(CyEVrefSource source, CyEGain gain)
        {
            this.VrefSource = source;
            this.Gain = gain;
        }

        public CyEVrefSource VrefSource { get; set; }
        public CyEGain Gain { get; set; }
    }

    #endregion

    // Begin custom component parameter code
    // End custom component parameter code

    public class ADC_UAB_Parameters
    {
        public const int MID_TAP = 8;
        public const int HIGH_TAP = 16;
        private readonly ICyInstEdit_v1 m_edit;
        public readonly ICyInstQuery_v1 m_query;
        public readonly ICyTerminalQuery_v1 m_termQuery;

        public ADC_UAB_Control control;

        // Begin component parameter variables
        private CyEInputEndedness m_endedness;
        private CyEGain m_vRange;
        private CyEVrefSource m_vrefSource;
        private int m_vrefTap;
        private bool m_showSoc;
        private UInt32 m_osr;
        private CyEBandgapGain m_bandgapGain;
        private double m_vddaVolts;
        // End component parameter variables

        public ADC_UAB_Parameters(ICyInstEdit_v1 edit)
            : this(edit, edit)
        {
        }

        public ADC_UAB_Parameters(ICyInstQuery_v1 query)
            : this(null, query)
        {
        }

        public ADC_UAB_Parameters(ICyInstEdit_v1 edit, ICyInstQuery_v1 query)
            : this(edit, query, null)
        {
        }

        public ADC_UAB_Parameters(ICyInstEdit_v1 edit, ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            this.m_edit = edit;
            this.m_query = query;
            this.m_termQuery = termQuery;
            GetParams();
        }

        public CyEInputEndedness Endedness
        {
            get { return m_endedness; }
            set
            {
                m_endedness = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.ENDEDNESS,
                        ((int)m_endedness).ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public CyEGain VRange
        {
            get { return m_vRange; }
            set
            {
                m_vRange = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.V_RANGE,
                        ((int)m_vRange).ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public CyEVrefSource VrefSource
        {
            get { return m_vrefSource; }
            set
            {
                m_vrefSource = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.VREF_SOURCE,
                        ((int)m_vrefSource).ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public int VrefTap
        {
            get { return m_vrefTap; }
            set
            {
                m_vrefTap = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.VREF_TAP,
                        (m_vrefTap).ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public bool ShowSoc
        {
            get { return m_showSoc; }
            set
            {
                m_showSoc = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.SHOW_SOC,
                        m_showSoc.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public UInt32 OSR
        {
            get { return m_osr; }
            set
            {
                m_osr = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.OSR,
                        (m_osr).ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        // This property comes from the design, not the component instance.
        public CyEBandgapGain BandgapGain
        {
            get { return m_bandgapGain; }
            set { m_bandgapGain = value; }
        }

        public double VddaVolts
        {
            get { return m_vddaVolts; }
            set { m_vddaVolts = value; }
        }
        // End component parameter properties
        
        // Load committed parameters from customizer
        public void GetParams()
        {
            if (m_query != null)
            {
                // Begin component parameter loading

                // Load Endedness component parameter
                try
                {
                    m_endedness = (CyEInputEndedness)
                        Convert.ToInt32(m_query.GetCommittedParam(
                        CyParamNames.ENDEDNESS).Value);
                }
                catch (Exception) { }

                // Load Gain component parameter
                try
                {
                    m_vRange = (CyEGain)
                        Convert.ToInt32(m_query.GetCommittedParam(
                        CyParamNames.V_RANGE).Value);
                }
                catch (Exception) { }

                // Load Vref source parameter.
                try
                {
                    m_vrefSource = (CyEVrefSource)
                        Convert.ToInt32(m_query.GetCommittedParam(
                        CyParamNames.VREF_SOURCE).Value);
                }
                catch (Exception) { }

                // Load Vref tap parameter.
                try
                {
                    m_vrefTap =
                        Convert.ToInt32(m_query.GetCommittedParam(
                        CyParamNames.VREF_TAP));
                }
                catch (Exception) { }

                // Load ShowSoc component parameter
                try
                {
                    m_showSoc = Convert.ToBoolean(m_query.GetCommittedParam(
                        CyParamNames.SHOW_SOC).Value);
                }
                catch (Exception) { }

                // Load OSR component parameter
                try
                {
                    m_osr = Convert.ToUInt32(m_query.GetCommittedParam(
                        CyParamNames.OSR).Value);
                }
                catch (Exception) { }

                // Load bandgap gain from design (if there is a design).
                m_bandgapGain = CyVoltage.GetDesignBandgapGain(this.m_query);

                // Load Vdda from design.
                m_vddaVolts = CyVoltage.GetDesignVddaValue(this.m_query);

                // End component parameter loading
            }
        }

        public void CommitParams()
        {
            if (m_edit != null)
            {
                if (!m_edit.CommitParamExprs())
                {
                    MessageBox.Show("Error in Committing Parameters");
                }
            }
        }
    }
}
