/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Windows.Forms;

namespace Comp_P4_v1_10
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        private readonly CyImage m_symbol;
        private readonly CyImage m_graph;

        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructor(s)
        public CyBasicTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();
            rbRisingEdge.CheckedChanged += rb_CheckedChanged;
            rbFallingEdge.CheckedChanged += rb_CheckedChanged;
            rbIgnoreEdges.CheckedChanged += rb_CheckedChanged;
            rbBothEdges.CheckedChanged += rb_CheckedChanged;
            rbHysteresisDisable.CheckedChanged += rb_CheckedChanged;
            rbHysteresisEnable.CheckedChanged += rb_CheckedChanged;
            rbPolarityInv.CheckedChanged += rb_CheckedChanged;
            rbPolarityNonInv.CheckedChanged += rb_CheckedChanged;
            rbSpeedSlow.CheckedChanged += rb_CheckedChanged;
            rbSpeedMedium.CheckedChanged += rb_CheckedChanged;
            rbSpeedHigh.CheckedChanged += rb_CheckedChanged;
            rb_DeepSleepDisabled.CheckedChanged += rb_CheckedChanged;
            rb_DeepSleepEnabled.CheckedChanged += rb_CheckedChanged;
            chB_IntOutEnabled.CheckedChanged += chB_CheckedChanged;           
            m_symbol = new CyImage();
            m_graph = new CyImage();
            RedrawGraphs();
        }

        #endregion

        #region Update UI
        public void UpdateUI()
        {
            rbHysteresisEnable.Checked = (m_params.Hysteresis == CyEHysteresisType.CMP_ENABLE_HYST);
            rbHysteresisDisable.Checked = !rbHysteresisEnable.Checked;

            rbPolarityInv.Checked = (m_params.Polarity == CyEPolarityType.CMP_INVERTING);
            rbPolarityNonInv.Checked = !rbPolarityInv.Checked;

            rbSpeedSlow.Checked = (m_params.Power == CyEPowerType.CMP_LOW_POWER);
            rbSpeedMedium.Checked = (m_params.Power == CyEPowerType.CMP_MED_POWER);
            rbSpeedHigh.Checked = (m_params.Power == CyEPowerType.CMP_HIGH_POWER);

            rb_DeepSleepEnabled.Checked = m_params.DeepSleep;
            rb_DeepSleepDisabled.Checked = !rb_DeepSleepEnabled.Checked;

            chB_IntOutEnabled.Checked = m_params.InterruptEnabled;

            rbIgnoreEdges.Checked = (m_params.Interrupt == CyEInterruptType.INTR_DISABLE);
            rbRisingEdge.Checked = (m_params.Interrupt == CyEInterruptType.INTR_RISING);
            rbFallingEdge.Checked = (m_params.Interrupt == CyEInterruptType.INTR_FALLING);
            rbBothEdges.Checked = (m_params.Interrupt == CyEInterruptType.INTR_BOTH);

            UpdateDeepSleepVisibility();
        }

        private void UpdateDeepSleepVisibility()
        {
            if (m_params.IsCTBmIPV0) //PSoC4100/4200
            {
                if (m_params.DeepSleep)
                {
                    errorProvider.SetError(rb_DeepSleepEnabled, String.Format(Resources.ErrMsgDeepSleep));
                    grB_DeepSleep.Enabled = true;
                }
                else
                {
                    errorProvider.SetError(rb_DeepSleepEnabled, String.Empty);
                    grB_DeepSleep.Enabled = false;
                }
            }
            else //PSoC 4200-BL
            {
                errorProvider.SetError(rb_DeepSleepEnabled, String.Empty);
                grB_DeepSleep.Enabled = true;
            }
        }

        private void CheckPolarity()
        {
            if(m_params.Polarity == CyEPolarityType.CMP_INVERTING && m_params.DeepSleep)
                errorProvider.SetError(rbPolarityInv, String.Format(Resources.ErrMsgPolarity));
            else errorProvider.SetError(rbPolarityInv, String.Empty);
        }

        private void RedrawGraphs()
        {
            m_graph.m_interrupt = m_params.Interrupt;

            m_graph.m_hysteresis = m_params.Hysteresis;
            m_graph.m_polarity = m_params.Polarity;
            m_graph.m_power = m_params.Power;
            m_graph.m_imageSize = pbGraph.Size;
            m_graph.UpdateGraph();
            pbGraph.Image = m_graph.m_bmp;

            m_symbol.m_hysteresis = m_params.Hysteresis;
            m_symbol.m_polarity = m_params.Polarity;
            m_symbol.m_power = m_params.Power;
            m_symbol.m_imageSize = pbSymbol.Size;
            m_symbol.UpdateSymbol();
            pbSymbol.Image = m_symbol.m_bmp;
        }
        #endregion

        #region Event handlers
        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton) sender;
            if (rb.Checked == false)
            {
                if (rb == rbPolarityInv && rb_DeepSleepEnabled.Checked)
                    rbPolarityInv.Enabled = false;
                else if (rb == rb_DeepSleepDisabled && !rbPolarityInv.Checked)
                    rbPolarityInv.Enabled = false;
                else if (rb == rb_DeepSleepEnabled)
                    rbPolarityInv.Enabled = true;

                return;
            }

            if (rb == rbHysteresisEnable)
                m_params.Hysteresis = CyEHysteresisType.CMP_ENABLE_HYST;
            else if (rb == rbHysteresisDisable)
                m_params.Hysteresis = CyEHysteresisType.CMP_DISABLE_HYST;
            else if (rb == rbPolarityInv)
                m_params.Polarity = CyEPolarityType.CMP_INVERTING;
            else if (rb == rbPolarityNonInv)
                m_params.Polarity = CyEPolarityType.CMP_NON_INVERTING;

            else if (rb == rbIgnoreEdges)
                m_params.Interrupt = CyEInterruptType.INTR_DISABLE;
            else if (rb == rbRisingEdge)
                m_params.Interrupt = CyEInterruptType.INTR_RISING;
            else if (rb == rbFallingEdge)
                m_params.Interrupt = CyEInterruptType.INTR_FALLING;
            else if (rb == rbBothEdges)
                m_params.Interrupt = CyEInterruptType.INTR_BOTH;

            else if (rb == rbSpeedSlow)
                m_params.Power = CyEPowerType.CMP_LOW_POWER;
            else if (rb == rbSpeedMedium)
                m_params.Power = CyEPowerType.CMP_MED_POWER;
            else if (rb == rbSpeedHigh)
                m_params.Power = CyEPowerType.CMP_HIGH_POWER;

            else if (rb == rb_DeepSleepDisabled)
            {
                m_params.DeepSleep = false;
                UpdateDeepSleepVisibility();
            }
            else if (rb == rb_DeepSleepEnabled)
            {
                m_params.DeepSleep = true;
                UpdateDeepSleepVisibility();
            }

            CheckPolarity();
            RedrawGraphs();

        }

        void chB_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptEnabled = chB_IntOutEnabled.Checked;
        }
        #endregion Event handlers
    }
}
