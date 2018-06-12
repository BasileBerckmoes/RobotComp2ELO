using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ADC_UAB_v1_0
{
    public partial class ADC_UAB_Control : UserControl
    {
        private ADC_UAB_Parameters parameters;
        private CyAdcUab m_adcUab;
        private bool m_updateParameters = false;

        public ADC_UAB_Control(ADC_UAB_Parameters parameters, CyAdcUab adcUab)
        {
            InitializeComponent();
            m_warningProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider.Icon = ADC_UAB_v1_0.ADC_UAB_Errors.WarningIco;
            this.parameters = parameters;
            this.m_adcUab = adcUab;
            UpdateForm();
            this.m_updateParameters = true;
            UpdateDerivedDisplays();
        }

        private void UpdateDerivedDisplays()
        {
            UpdateDisplayedValues();
            UpdateToolTips();
            UpdateGuiErrors();
            UpdateGuiNotes();
            updateInputRanges();
        }

        private void updateInputRanges()
        {
            bool updateState = this.m_updateParameters;
            this.m_updateParameters = false;

            int gainSelection = this.m_cmbGain.SelectedIndex;

            this.m_cmbGain.DisplayMember = "Display";
            this.m_cmbGain.ValueMember = "Value";
            if (this.m_rbDifferential.Checked == true)
            {
                this.m_cmbGain.DataSource = this.m_adcUab.GetDifferentialRanges();
            }
            else
            {
                this.m_cmbGain.DataSource = this.m_adcUab.GetSingleEndedRanges();
            }

            this.m_cmbGain.SelectedIndex = gainSelection;

            this.m_updateParameters = updateState;
        }

        private void UpdateDisplayedValues()
        {
            this.m_lRowHeader.Text = this.m_adcUab.Vlabel();
            this.m_lVoltsMax.Text = this.m_adcUab.VmaxVolts();
            this.m_lVoltsMid.Text = this.m_adcUab.VmidVolts();
            this.m_lVoltsMin.Text = this.m_adcUab.VminVolts();
            this.m_lConvTime.Text = this.m_adcUab.ConvTime();
            this.m_lMaxSourceImp.Text = this.m_adcUab.MaxSourceImp();
            this.m_lCodeMax.Text = this.m_adcUab.MaxCode();
            this.m_lCodeMin.Text = this.m_adcUab.MinCode();
        }

        private void UpdateToolTips()
        {
            if (this.parameters.Endedness == CyEInputEndedness.Differential)
            {
                this.m_toolTip.SetToolTip(this.m_lRowHeader,
                    global::ADC_UAB_v1_0.ADC_UAB_Tooltip.vdiffToolTip);
            }
            else
            {
                this.m_toolTip.SetToolTip(this.m_lRowHeader,
                    global::ADC_UAB_v1_0.ADC_UAB_Tooltip.vinToolTip);
            }
        }

        private void UpdateGuiNotes()
        {
            var control = this.m_lVoltsMax;
            var saturateNotice
                = (this.m_adcUab.IsSaturateMax() == true)
                ? ADC_UAB_Errors.saturateHighError
                : "";
            this.m_noteProvider.SetIconAlignment(control, ErrorIconAlignment.MiddleRight);
            this.m_noteProvider.SetError(control, saturateNotice);

            control = this.m_lVoltsMin;
            saturateNotice 
                = (this.m_adcUab.IsSaturateMin() == true)
                ? ADC_UAB_Errors.saturateLowError
                : "";
            this.m_noteProvider.SetIconAlignment(control, ErrorIconAlignment.MiddleRight);
            this.m_noteProvider.SetError(control, saturateNotice);

            //Conversion time note
            control = this.m_lbConvTime;
            var conversionNotice
                = (this.m_adcUab.IsConvTimeInBounds() == false)
                ? this.m_adcUab.ConversionTimeErrorMessage()
                : "";
            this.m_noteProvider.SetIconAlignment(control, ErrorIconAlignment.MiddleRight);
            this.m_noteProvider.SetError(control, conversionNotice);

        }
        private void UpdateGuiErrors()
        {
            var control = this.m_lConvTime;
            var sysClkNotice
                = (this.m_adcUab.IsSysClkOK() == false)
                ? CyAdcUab.SysClkErrorMessage()
                : "";
            this.m_warningProvider.SetIconAlignment(control, ErrorIconAlignment.MiddleLeft);
            this.m_warningProvider.SetError(control, sysClkNotice);
        }

        private void SetToolTips()
        {
            // Input groupbox tooltips.
            this.m_toolTip.SetToolTip(this.m_rbDifferential,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.diffToolTip);
            this.m_toolTip.SetToolTip(this.m_rbSingleEnded,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.singleEndedToolTip);

            // Trigger groupbox tooltips.
            this.m_toolTip.SetToolTip(this.m_rbHardware,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.useSocToolTip);
            this.m_toolTip.SetToolTip(this.m_rbSoftware,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.useSocToolTip);

            // Reference groupbox tooltips.
            this.m_toolTip.SetToolTip(this.m_lbGain,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.inputRangeToolTip);
            this.m_toolTip.SetToolTip(this.m_cmbGain,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.inputRangeToolTip);

            // Timing groupbox tooltips.
            this.m_toolTip.SetToolTip(this.m_lConvTime,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.convTimeToolTip);
            this.m_toolTip.SetToolTip(this.m_lbConvTime,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.convTimeToolTip);
            this.m_toolTip.SetToolTip(this.m_lbMaxSourceImp,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.maxSourceImpToolTip);
            this.m_toolTip.SetToolTip(this.m_lMaxSourceImp,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.maxSourceImpToolTip);

            // Transfer function groupbox tooltips.
            this.m_toolTip.SetToolTip(this.m_lCodeMax,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.maxCodeToolTip);
            this.m_toolTip.SetToolTip(this.m_lVoltsMax,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.maxVoltsToolTip);
            this.m_toolTip.SetToolTip(this.m_lCodeMid,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.midCodeToolTip);
            this.m_toolTip.SetToolTip(this.m_lVoltsMid,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.midVoltsToolTip);
            this.m_toolTip.SetToolTip(this.m_lCodeMin,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.minCodeToolTip);
            this.m_toolTip.SetToolTip(this.m_lVoltsMin,
                global::ADC_UAB_v1_0.ADC_UAB_Tooltip.minVoltsToolTip);
        }

        private void m_rbHardware_CheckedChanged(object sender, EventArgs e)
        {
            if (this.m_updateParameters == true)
            {
                if (this.m_rbHardware.Checked == true)
                {
                    this.parameters.ShowSoc = true;
                    UpdateDerivedDisplays();
                }
            }
        }

        private void m_rbSoftware_CheckedChanged(object sender, EventArgs e)
        {
            if (this.m_updateParameters == true)
            {
                if (this.m_rbSoftware.Checked == true)
                {
                    this.parameters.ShowSoc = false;
                    UpdateDerivedDisplays();
                }
            }
        }

        private void m_rbDifferential_CheckedChanged(object sender, EventArgs e)
        {
            if (this.m_updateParameters == true)
            {
                if (this.m_rbDifferential.Checked == true)
                {
                    this.parameters.Endedness
                        = CyEInputEndedness.Differential;
                    UpdateDerivedDisplays();
                }
            }
        }

        private void m_rbSingleEnded_CheckedChanged(object sender, EventArgs e)
        {
            if (this.m_updateParameters == true)
            {
                if (this.m_rbSingleEnded.Checked == true)
                {
                    this.parameters.Endedness
                        = CyEInputEndedness.SingleEnded;
                    UpdateDerivedDisplays();
                }
            }
        }

        private void m_cmbGain_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.m_updateParameters == true)
            {
                var displayValue = (CyDisplayValue<CyVrefGainPair>)m_cmbGain.SelectedItem;
                if (displayValue != null)
                {
                    this.parameters.VRange = displayValue.Value.Gain;
                    this.parameters.VrefSource = displayValue.Value.VrefSource;
                    this.parameters.VrefTap
                        = CyRange.VrefTap(this.parameters.VrefSource, this.parameters.BandgapGain);
                }
                UpdateDerivedDisplays();
            }
        }

        private void m_tbCodeMax_TextChanged(object sender, EventArgs e)
        {

        }

        // End parameter control event handlers
    }
}
