/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
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
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace LPComp_P4_v2_20
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        readonly CyImage m_symbol;
        readonly CyImage m_graph;

        private ErrorProvider errorProviderOutConfig;

        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructor(s)
        public CyBasicTab(CyParameters param)
            : base(param)
        {
            m_params.BasicTab = this;            

            InitializeComponent();

            rbHysteresisDisable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbHysteresisEnable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptDisabled.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptRising.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptFalling.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptBoth.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSynchronized.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbDirect.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbPulse.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedSlow.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedMedium.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedHigh.CheckedChanged += new EventHandler(rb_CheckedChanged);
            chB_IntEnabled.CheckedChanged += new EventHandler(chB_CheckedChanged);            

            m_symbol = new CyImage();
            m_graph = new CyImage();
            RedrawGraphs();

            errorProviderOutConfig = new ErrorProvider();
            errorProviderOutConfig.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            errorProviderOutConfig.ContainerControl = this;
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            rbHysteresisEnable.Checked = (m_params.Hysteresis == CyEHysteresisType.LPC_ENABLE_HYST);
            rbHysteresisDisable.Checked = !rbHysteresisEnable.Checked;

            rbSynchronized.Checked = (m_params.OutputMode == CyEOutputModeType.OUT_MODE_SYNC);
            rbDirect.Checked = (m_params.OutputMode == CyEOutputModeType.OUT_MODE_DIRECT);
            rbPulse.Checked = (m_params.OutputMode == CyEOutputModeType.OUT_MODE_PULSE);

            rbInterruptDisabled.Checked = (m_params.Interrupt == CyEInterruptType.LPC_INT_DISABLE);
            rbInterruptRising.Checked = (m_params.Interrupt == CyEInterruptType.LPC_INT_RISING);
            rbInterruptFalling.Checked = (m_params.Interrupt == CyEInterruptType.LPC_INT_FALLING);
            rbInterruptBoth.Checked = (m_params.Interrupt == CyEInterruptType.LPC_INT_BOTH);

            rbSpeedSlow.Checked = (m_params.Speed == CyESpeedType.LPC_LOW_SPEED);
            rbSpeedMedium.Checked = (m_params.Speed == CyESpeedType.LPC_MED_SPEED);
            rbSpeedHigh.Checked = (m_params.Speed == CyESpeedType.LPC_HIGH_SPEED);

            chB_IntEnabled.Checked = m_params.InterruptEnabled;
            label_Note2.Visible = !m_params.IsLPCompIPV2;
            labelNote2SuperscriptRising.Visible = !m_params.IsLPCompIPV2;
            labelNote2SuperscriptFalling.Visible = !m_params.IsLPCompIPV2;

            UpdateOutputConfigVisibility();
        }

        private void UpdateOutputConfigVisibility()
        {
            if (m_params.IsLPCompIPV0) // PSoC 4100/4200
            {
                if (m_params.OutputMode != CyEOutputModeType.OUT_MODE_PULSE)
                {
                    if (m_params.OutputMode == CyEOutputModeType.OUT_MODE_SYNC)
                    {
                        errorProviderOutConfig.SetError(rbSynchronized, Resources.ErrMsgOutputConfig);
                        errorProviderOutConfig.SetError(rbDirect, String.Empty);
                    }
                    else
                    {
                        errorProviderOutConfig.SetError(rbDirect, Resources.ErrMsgOutputConfig);
                        errorProviderOutConfig.SetError(rbSynchronized, String.Empty);
                    }
                    groupBoxOuputConfig.Enabled = true;
                }
                else
                {
                    errorProviderOutConfig.SetError(rbSynchronized, String.Empty);
                    errorProviderOutConfig.SetError(rbDirect, String.Empty);
                    groupBoxOuputConfig.Enabled = false;
                }
                chB_IntEnabled.Enabled = false;
                labelNote1SuperscriptInt.Enabled = false;
            }
            else if (m_params.IsLPCompIPV2) // PSoC 4200-BL
            {
                errorProviderOutConfig.SetError(rbSynchronized, String.Empty);
                groupBoxOuputConfig.Enabled = true;
                chB_IntEnabled.Enabled = true;
                labelNote1SuperscriptInt.Enabled = true;
            }
        }

        public void RedrawGraphs()
        {
            m_graph.UpdateParams(m_params, pbGraph);
            m_graph.UpdateGraph();
            pbGraph.Image = m_graph.Bmp;

            m_symbol.UpdateParams(m_params, pbSymbol);
            m_symbol.UpdateSymbol();
            pbSymbol.Image = m_symbol.Bmp;

            if (m_params.AdvancedTab!=null) m_params.AdvancedTab.RedrawSymbol();
        }
        #endregion

        #region Event handlers
        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false) 
                /* Checked is false (because the value maps to an enum and the radio button that is checked
                 * will set the value).
                 */
                return;

            else if (rb == rbHysteresisEnable)
                m_params.Hysteresis = CyEHysteresisType.LPC_ENABLE_HYST;
            else if (rb == rbHysteresisDisable)
                m_params.Hysteresis = CyEHysteresisType.LPC_DISABLE_HYST;

            else if (rb == rbInterruptDisabled)
                m_params.Interrupt = CyEInterruptType.LPC_INT_DISABLE;
            else if (rb == rbInterruptRising)
                m_params.Interrupt = CyEInterruptType.LPC_INT_RISING;
            else if (rb == rbInterruptFalling)
                m_params.Interrupt = CyEInterruptType.LPC_INT_FALLING;
            else if (rb == rbInterruptBoth)
                m_params.Interrupt = CyEInterruptType.LPC_INT_BOTH;

            else if (rb == rbSynchronized)
                m_params.OutputMode = CyEOutputModeType.OUT_MODE_SYNC;
            else if (rb == rbDirect)
                m_params.OutputMode = CyEOutputModeType.OUT_MODE_DIRECT;
            else if (rb == rbPulse)
                m_params.OutputMode = CyEOutputModeType.OUT_MODE_PULSE;

            else if (rb == rbSpeedSlow)
                m_params.Speed = CyESpeedType.LPC_LOW_SPEED;
            else if (rb == rbSpeedMedium)
                m_params.Speed = CyESpeedType.LPC_MED_SPEED;
            else if (rb == rbSpeedHigh)
                m_params.Speed = CyESpeedType.LPC_HIGH_SPEED;

            RedrawGraphs();
            UpdateOutputConfigVisibility();
        }

        void chB_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptEnabled = chB_IntEnabled.Checked;
            UpdateOutputConfigVisibility();
        }
        #endregion Event handlers
    }
}
