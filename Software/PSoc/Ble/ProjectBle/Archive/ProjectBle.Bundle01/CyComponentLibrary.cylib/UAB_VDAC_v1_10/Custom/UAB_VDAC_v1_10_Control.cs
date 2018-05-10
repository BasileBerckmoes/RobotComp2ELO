/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace UAB_VDAC_v1_10
{
    public partial class CyUAB_VDAC_v1_10Control : UserControl
    {
        private CyParameters m_parameters;
        private CyTransferControl m_transferControl;
        protected ErrorProvider m_errorProvider = null;
        protected ErrorProvider m_warningProvider = null;
        protected ErrorProvider m_noteProvider = null;

        //Constructor
        public CyUAB_VDAC_v1_10Control(CyParameters parameters)
        {
            InitializeComponent();

            this.m_parameters = parameters;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider = new ErrorProvider();
            m_warningProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_noteProvider = new ErrorProvider();
            m_noteProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.m_transferControl = new CyTransferControl(this.m_parameters);
            this.m_tdTransferDiagramPanel.Controls.Add(this.m_transferControl);
            this.m_transferControl.Dock = DockStyle.Fill;

            this.m_cmbDacMode.Items.Clear();
            this.m_cmbDacMode.Items.AddRange(m_parameters.m_dacMode.EnumDisplayList);

            this.m_cmbVrefSource.Items.Clear();
            this.m_cmbVrefSource.Items.AddRange(m_parameters.m_vrefSrc.EnumDisplayList);

            this.m_cmbVagndSource.Items.Clear();
            this.m_cmbVagndSource.Items.AddRange(m_parameters.m_vagndSrc.EnumDisplayList);

            this.m_cmbDacGain.Items.Clear();
            this.m_cmbDacGain.Items.Add("Vagnd ± Vref");
            for (int i = 1; i < 3; i++)
            {
                this.m_cmbDacGain.Items.Add("Vagnd ± " + Math.Pow(2, i).ToString() + "Vref");
            }

            this.m_transferControl.CodeVoltPairChanged += defaultOutVoltsTransferDiagram_Scroll;
            this.m_nudDefaultOutVolts.Value = Math.Min(Math.Max(m_nudDefaultOutVolts.Minimum, (decimal)m_parameters.DefaultOutVolt), m_nudDefaultOutVolts.Maximum);
            UpdateForm();

            this.AutoScroll = true;
        }

        // Updates form with saved parameters when the GUI is opened.
        public void UpdateForm()
        {
            // Begin parameter custom control update
            // End parameter custom control update

            // Begin parameter default control update
            m_cmbDacMode.SelectedItem = m_parameters.m_dacMode.Display;
            m_cmbDacGain.SelectedIndex = Convert.ToInt16(Math.Log(Convert.ToInt16(m_parameters.DacGain), 2));
            m_cmbVrefSource.SelectedItem = m_parameters.m_vrefSrc.Display;
            m_cmbVagndSource.SelectedItem = m_parameters.m_vagndSrc.Display;
            m_nudDefaultOutVolts.Value = Math.Min(Math.Max(m_nudDefaultOutVolts.Minimum, (decimal)m_parameters.DefaultOutVolt), m_nudDefaultOutVolts.Maximum);
            m_nudVrefVolts.Value = Math.Min(Math.Max(m_nudVrefVolts.Minimum, (decimal)m_parameters.VrefVolts), m_nudVrefVolts.Maximum);
            m_nudVagndVolts.Value = Math.Min(Math.Max(m_nudVagndVolts.Minimum, (decimal)m_parameters.VagndVolts), m_nudVagndVolts.Maximum);

            m_rbClockExternal.Checked = m_parameters.ClockIsExternal;
            m_rbClockInternal.Checked = !m_parameters.ClockIsExternal;
            nud_ValueChanged(m_nudClockFreq, new EventArgs());

            m_rbModulatorNone.Checked = !m_parameters.ModbitIsExternal;
            m_rbModulatorExternal.Checked = m_parameters.ModbitIsExternal;

            m_rbStrobeContinous.Checked = !m_parameters.StrobeIsExternal;
            m_rbStrobeExternal.Checked = m_parameters.StrobeIsExternal;

            m_rbOutputFeedback.Checked = m_parameters.BufferIsFeedback;
            m_rbOutputFollower.Checked = !m_parameters.BufferIsFeedback;

        }

        private void nud_ValueChanged(object sender, EventArgs e)
        {
            if (sender == m_nudDefaultOutVolts)
            {
                this.m_parameters.DefaultOutVolt = (float)(this.m_nudDefaultOutVolts.Value);
                this.m_parameters.DefaultOutCode = m_transferControl.m_diagram.Voltage2Code((float)this.m_nudDefaultOutVolts.Value);
                /* Parameter has changed, update corresponding controls.*/
                helper_DefaultOutChanged(sender);
            }
            else if (sender == m_nudVrefVolts)
            {
                helper_ClearNotifications(m_nudVrefVolts);
                /* Limit the values supported to Vdd */
                if ((double)this.m_nudVrefVolts.Value > m_parameters.Chip_Max_V)
                {
                    this.m_nudVrefVolts.Value = Convert.ToDecimal(m_parameters.Chip_Max_V);
                }
                else
                {
                    this.m_parameters.VrefVolts = (double)this.m_nudVrefVolts.Value;
                }
                /* Provide a warning for values entered that are outside of the recommended range. */
                if (((double)this.m_nudVrefVolts.Value > m_parameters.Range_VrefMax) ||
                    ((double)this.m_nudVrefVolts.Value < m_parameters.Range_VrefMin))
                {
                    m_warningProvider.SetError(m_nudVrefVolts, String.Format(UAB_VDAC_v1_10_resource.vrefWarning, m_parameters.Range_VrefMin, m_parameters.Range_VrefMax));
                }
                /* Call dacSelectComboBox to sync Vagnd to Vref and update default trackbar if needed. 
                 * SetVSourceEnableStates(); UpdateDefam_nudVrefVolts.ValueultOutTrackbar(); are called in m_cbDacSelect_SelectedIndexChanged*/
                UpdateDefaultOutTrackbar();
                cmb_SelectedIndexChanged(sender, e);
            }
            else if (sender == m_nudVagndVolts)
            {
                helper_ClearNotifications(m_nudVagndVolts);
                /* Limit the values supported to Vdd */
                if ((double)this.m_nudVagndVolts.Value > m_parameters.Chip_Max_V)
                {
                    this.m_nudVagndVolts.Value = Convert.ToDecimal(m_parameters.Chip_Max_V);
                }
                else
                {
                    this.m_parameters.VagndVolts = (double)this.m_nudVagndVolts.Value;
                }
                /* Provide a warning for values entered that are outside of the recommended range. */
                if ((double)this.m_nudVagndVolts.Value > m_parameters.Range_VagndMax ||
                    (double)this.m_nudVagndVolts.Value < m_parameters.Range_VagndMin)
                {
                    m_warningProvider.SetError(m_nudVagndVolts, String.Format(UAB_VDAC_v1_10_resource.vagndWarning, m_parameters.Range_VagndMin, m_parameters.Range_VagndMax));
                }
                UpdateDefaultOutTrackbar();
            }
            else if (sender == m_nudClockFreq)
            {
                // If internal clock, parameter needs editing.  Otherwise, it doesn't.
                // Always set the Refresh rate to half nud.Value.
                if (!m_rbClockExternal.Checked)
                {
                    this.m_parameters.UserRefClkRate_kHz = (double)this.m_nudClockFreq.Value;
                }
                m_lClockRefreshValue.Text = (m_nudClockFreq.Value / 4).ToString("0.0") + " kHz";

                helper_ClearNotifications(m_nudClockFreq);
                if ((double)this.m_nudClockFreq.Value > m_parameters.Range_FreqMax ||
                    (double)this.m_nudClockFreq.Value < m_parameters.Range_FreqMin)
                {
                    m_warningProvider.SetError(m_nudClockFreq, String.Format(UAB_VDAC_v1_10_resource.clkWarning, m_parameters.Range_FreqMin, m_parameters.Range_FreqMax));
                }
                UpdateDefaultOutTrackbar();
            }
        }

        private void cmb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sender == m_cmbDacMode)
            {
                this.m_parameters.m_dacMode.Display = m_cmbDacMode.SelectedItem.ToString();
                
                m_parameters.RecalculateVoltageClips();
                SetVSourceEnableStates();
                UpdateDefaultOutTrackbar();
            }
            else if (sender == m_cmbDacGain)
            {
                this.m_parameters.DacGain = (Int16)(Math.Pow(2, this.m_cmbDacGain.SelectedIndex));
                UpdateDefaultOutTrackbar();
            }
            else if (sender == m_cmbVrefSource)
            {
                this.m_parameters.m_vrefSrc.Display = this.m_cmbVrefSource.SelectedItem.ToString();
                SetVSourceEnableStates();
            }
            else if (sender == m_cmbVagndSource)
            {
                this.m_parameters.m_vagndSrc.Display = this.m_cmbVagndSource.SelectedItem.ToString();
                SetVSourceEnableStates();
            }
        }
        
        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_rbStrobeContinous || sender == m_rbStrobeExternal)
            {
                this.m_parameters.StrobeIsExternal = (bool)this.m_rbStrobeExternal.Checked;
            }
            else if (sender == m_rbOutputFeedback || sender == m_rbOutputFollower)
            {
                this.m_parameters.BufferIsFeedback = (bool)this.m_rbOutputFeedback.Checked;
            }
            else if (sender == m_rbModulatorExternal || sender == m_rbModulatorNone)
            {
                this.m_parameters.ModbitIsExternal = (bool)this.m_rbModulatorExternal.Checked;
            }
            else if (sender == m_rbClockExternal || sender == m_rbClockInternal)
            {
                double tmpClockFrequency_kHz;
                bool tmpClockIsExternal = (bool)this.m_rbClockExternal.Checked;
                this.m_parameters.ClockIsExternal = tmpClockIsExternal;
                this.m_nudClockFreq.Enabled = !tmpClockIsExternal;
                // If external, query. If internal, load parameter
                // Divide by 1000 to convert Hz to kHz.
                tmpClockFrequency_kHz = tmpClockIsExternal ? CyClock.GetClockRate_Hz(m_parameters.TermQuery, CyTerminalNames.CLOCK_TERM) / 1000 : m_parameters.UserRefClkRate_kHz;

                //An unsuccessful query will return -1.  If this is the case, don't update the nud.
                if (tmpClockFrequency_kHz > 0)
                {
                    m_nudClockFreq.Visible = true;
                    m_lClockRefreshValue.Visible = true;
                    m_lClockRefresh.Text = "Refresh rate:";
                    m_nudClockFreq.Value = Math.Min(Math.Max(m_nudClockFreq.Minimum, (decimal)tmpClockFrequency_kHz), m_nudClockFreq.Maximum);
                }
                else
                {
                    m_nudClockFreq.Visible = false;
                    m_lClockRefreshValue.Visible = false;
                    m_lClockRefresh.Text = "Clock not connected.";
                }
                

            }
            else { }//if(sender == rb<Various radio buttons>)
        }

        private void defaultOutVoltsTransferDiagram_Scroll(object sender, EventArgs e)
        {
            this.m_parameters.DefaultOutCode = (int) m_transferControl.CodeVoltPair.X;
            this.m_parameters.DefaultOutVolt = m_transferControl.CodeVoltPair.Y;

            helper_DefaultOutChanged(sender);
        }

        private void helper_DefaultOutChanged(object sender)
        {
            decimal tmpOutVolts = (decimal)this.m_parameters.DefaultOutVolt;
            
            /* If one of the non-nud controls caused update, update the nud*/
            if (sender != this.m_nudDefaultOutVolts)
            {
                m_nudDefaultOutVolts.Value = Math.Min(Math.Max(m_nudDefaultOutVolts.Minimum, tmpOutVolts), m_nudDefaultOutVolts.Maximum);
                /* Update the NUD. Saturate it. */
            }


            /* If one of the non-transfercontrol contols caused value update, then update the transfercontrol*/
            if (sender != this.m_transferControl)
            {
                //update m_transferControl.SelectedScaled
                m_transferControl.CodeVoltPair = new PointF((float)m_parameters.DefaultOutCode, 
                                                              (float)m_parameters.DefaultOutVolt);
            }
        }
        
        private void SetVSourceEnableStates()
        {
            /* If Vref Source is Internal (PRB)... */
            if (m_parameters.m_vrefSrc.Display == m_parameters.m_vrefSrc.ValueToDisplay(DacVinSource.SOURCE_INTERNAL))
            {
                this.m_nudVrefVolts.Value = (decimal)m_parameters.InstQuery.VoltageQuery.SystemReference;
                this.m_nudVrefVolts.Enabled = false; /*Disable corresponding NUD*/
            }
            else
            {
                this.m_nudVrefVolts.Enabled = true;
            }

            /* If Vagnd Source is Internal (PRB)... */
            if (m_parameters.m_vagndSrc.Display == m_parameters.m_vagndSrc.ValueToDisplay(DacVinSource.SOURCE_INTERNAL))
            {
                this.m_nudVagndVolts.Value = (decimal)m_parameters.InstQuery.VoltageQuery.SystemReference;
                this.m_nudVagndVolts.Enabled = false; /*Disable corresponding NUD*/
            }
            else
            {
                this.m_nudVagndVolts.Enabled = true;
            }           
        }
        
        private void UpdateDefaultOutTrackbar()
        {
            if( m_nudDefaultOutVolts.Maximum != (decimal) m_parameters.MaximumOutputVoltage ||
            m_nudDefaultOutVolts.Minimum != (decimal)m_parameters.MinimumOutputVoltage)
            {
                 m_nudDefaultOutVolts.Maximum = (decimal) m_parameters.MaximumOutputVoltage;
                 m_nudDefaultOutVolts.Minimum = (decimal)m_parameters.MinimumOutputVoltage;
            }
            nud_ValueChanged(m_nudDefaultOutVolts, null);
            
        }

        //Function has signature of CyDesignUpdated_v1 delegate.  Called
        // during a customizer editing session if Creator updates its design.
        // (Usually when user hits "Apply")
        public void helper_DesignUpdated(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 terminalQuery)
        {
            rb_CheckedChanged(m_rbClockExternal, EventArgs.Empty);
        }

        private void helper_ClearNotifications(Control control)
        {
            m_errorProvider.SetError(control, String.Empty);
            m_warningProvider.SetError(control, String.Empty);
            m_noteProvider.SetError(control, String.Empty);
        }
        // End parameter control event handlers

    }
}
