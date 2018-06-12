/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace WaveDAC8_v2_10
{
    public partial class CyWaveDacTab : CyEditingWrapperControl
    {
        private CyWaveformControl[] m_cyWaveformControls = new CyWaveformControl[2];
        private CyClockingControl m_clockControl;

        // Order ranges for combo box display
        private CyEWaveRangeType[] m_orderedRangeList = new CyEWaveRangeType[]
        {
            CyEWaveRangeType.Range_1_Volt,
            CyEWaveRangeType.Range_1_Volt_Buffered,
            CyEWaveRangeType.Range_4_Volt,
            CyEWaveRangeType.Range_4_Volt_Buffered,
            CyEWaveRangeType.ISink_2040_uA,
            CyEWaveRangeType.ISink_256_uA,
            CyEWaveRangeType.ISink_32_uA,
            CyEWaveRangeType.ISource_2040_uA,
            CyEWaveRangeType.ISource_256_uA,
            CyEWaveRangeType.ISource_32_uA
        };

        public CyWaveDacTab()
        {
            InitializeComponent();
        }

        public CyWaveDacTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();
           
            CyAuxFunctions.FillComboFromList<CyEWaveRangeType>(m_cbRange, m_orderedRangeList);
            CreateWaveControls();
            CreateClockControl();
            SetMinSize();

            UpdateUIFromParams();
        }

        public override string TabName
        {
            get { return "Basic"; }
        }

        private void CreateWaveControls()
        {
            for (int i = 0; i < m_cyWaveformControls.Length; i++)
            {
                CyWaveformControl cyWaveform = new CyWaveformControl(i+1, m_parameters);
                m_cyWaveformControls[i] = cyWaveform;
                SplitterPanel panel = (i == 0) ? m_splitContainer.Panel1 : m_splitContainer.Panel2;
                panel.Controls.Add(cyWaveform);
                cyWaveform.Dock = DockStyle.Fill;
            }
        }

        private void CreateClockControl()
        {
            m_clockControl = new CyClockingControl(m_parameters);
            m_pnlHeader.Controls.Add(m_clockControl);
            m_clockControl.Left = m_pnlHeader.Width - 1 - m_clockControl.Width;
            m_clockControl.Top = 4;
            m_clockControl.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            m_clockControl.SampleRateChanged += clockControl_SampleRateChanged;
            m_pnlHeader.Height = m_clockControl.Top + m_clockControl.Height;
        }

        private void SetMinSize()
        {
            Size waveformMinSize = m_cyWaveformControls[0].GetMinSize();
            int topPanelMinWidth = m_cbRange.Left + m_cbRange.Width + m_clockControl.Width + 3;

            m_splitContainer.MinimumSize = new Size(waveformMinSize.Width, waveformMinSize.Height * 2);
            this.AutoScrollMinSize = new Size(Math.Max(m_splitContainer.MinimumSize.Width, topPanelMinWidth),
               m_splitContainer.MinimumSize.Height + m_splitContainer.Location.Y);
        }

        void clockControl_SampleRateChanged(object sender, CySampleRateChangedEventArgs e)
        {
            for (int i = 0; i < m_cyWaveformControls.Length; i++)
            {
                m_cyWaveformControls[i].UpdateSampleRate(e.SampleRate);
            }
        }

        public void UpdateUIFromParams()
        {
            CyAuxFunctions.SetComboValue(m_cbRange, m_parameters.DACRange);

            // Update clocking params
            for (int i = 0; i < m_cyWaveformControls.Length; i++)
			{
                m_cyWaveformControls[i].UpdateUIFromParams();
			}

            m_clockControl.UpdateUIFromParams();
        }

        public void UpdateDesign(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            m_clockControl.UpdateDesign();
        }

        private void cbRange_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEWaveRangeType prevRange = m_parameters.DACRange;
            m_parameters.DACRange = CyAuxFunctions.GetComboValue<CyEWaveRangeType>(m_cbRange);

            for (int i = 0; i < m_cyWaveformControls.Length; i++)
            {
                m_cyWaveformControls[i].UpdateVoltageRange(prevRange != m_parameters.DACRange);
            }
            m_clockControl.UpdateVoltageRange();
        }
    }
}


