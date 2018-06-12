/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace CSD_Comp_P4_v1_0.Tabs
{
    public partial class CyConfigTab : CyTabControlWrapper
    {
        #region Consts

        private const string ADJVREF_ITEM_FORMAT2 = "{0:" + VOLTAGE_DISPLAY_FORMAT_GUI + "} (tap {1})";

        #endregion Consts

        #region CyTabControlWrapper Override

        public override string TabName
        {
            get { return CyCustomizer.GENERAL_SYMBOL_TAB_NAME; }
        }

        #endregion CyTabControlWrapper Override

        #region Class Members 

        private readonly CyImage m_graph;

        #endregion Class Members

        #region Constructors

        public CyConfigTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            m_params = param;
            m_graph = new CyImage();

            UpdateUiFromTable();
        }

        #endregion Constructors

        #region Update UI

        public void UpdateUiFromTable()
        {
            // Update labels
            m_lblBandgap.Text = m_params.Bandgap.ToString(VOLTAGE_DISPLAY_FORMAT_GUI);
            m_lblVdda.Text = string.Format(Properties.Resources.VDDA_VALUE_FORMATSTR1, m_params.Vdda.ToString(
                VOLTAGE_DISPLAY_FORMAT_GUI));

            // Update reference source radioButtons
            if (m_params.RefSource == CyEnumRefSourceType.INTERNAL_BANDGAP)
                rbInternalBandgap.Checked = true;
            else if (m_params.RefSource == CyEnumRefSourceType.EXTERNAL_REFERENCE)
                rbExternalReference.Checked = true;
            else
                Debug.Assert(false);

            // Update reference type radioButtons
            if (m_params.RefType == CyEnumRefType.ADJUSTABLE)
                rbAdjustable.Checked = true;
            else if (m_params.RefType == CyEnumRefType.FIXED)
                rbFixed.Checked = true;
            else
                Debug.Assert(false);

            // Update adjustable Vref comboBox
            if (m_cmbxAdjustableVref.Items.Count > CyParameters.MAX_TAP_NUMBER - m_params.Tap &&
                0 <= CyParameters.MAX_TAP_NUMBER - m_params.Tap)
            {
                m_cmbxAdjustableVref.SelectedIndex = CyParameters.MAX_TAP_NUMBER - m_params.Tap; 
            }

            // Update voltageNumericUpDowns
            if (m_params.Vinref <= (double)numVinref.Maximum &&
                m_params.Vinref >= (double)numVinref.Minimum)
            {
                numVinref.Value = Convert.ToDecimal(m_params.Vinref);
            }

            if (m_params.VrangeDesired <= (double)numVrange.Maximum &&
                m_params.VrangeDesired >= (double)numVrange.Minimum)
            {
                numVrange.Value = Convert.ToDecimal(m_params.VrangeDesired); 
            }

            RedrawGraphs();
            UpdateVrefComboBoxItems();
        }

        private void RedrawGraphs()
        {
            m_graph.Speed = CyEnumSpeedType.FAST_SPEED;
            m_graph.m_imageSize = pbGraph.Size;
            m_graph.UpdateGraph();
            pbGraph.Image = m_graph.m_bmp;
        }

        private void UpdateVrefComboBoxItems()
        {
            // selection changes in this method should not cause the cmbxAdjustableVref_SelectedIndexChanged handler
            // because cmbxAdjustableVref_SelectedIndexChanged calls this method
            m_cmbxAdjustableVref.SelectedIndexChanged -= cmbxAdjustableVref_SelectedIndexChanged;

            byte tapNumber;
            int newSelectedComboBoxIndex = -1;
            int selectedTapNumber = m_params.Tap;
            double tapVoltage;
            double vRangeActual = m_params.VrangeActual;

            // remove all items and create a list of new items with new voltage values
            m_cmbxAdjustableVref.Items.Clear();
            for (int i = 0; i < CyParameters.MAX_TAP_NUMBER; i++)
            {
                tapNumber = (byte)(CyParameters.MAX_TAP_NUMBER - i);
                tapVoltage = vRangeActual - vRangeActual / CyParameters.MAX_TAP_NUMBER * i;

                // if the tap number was selected before add to the list even if value is less than MIN_TAP_VOLTAGE
                // if value is less than MIN_TAP_VOLTAGE add an error
                if (selectedTapNumber == tapNumber)
                {
                    m_cmbxAdjustableVref.Items.Add(new CyAdjVref(tapNumber, tapVoltage));
                    newSelectedComboBoxIndex = m_cmbxAdjustableVref.Items.Count - 1;

                    if (tapVoltage >= CyParameters.MIN_TAP_VOLTAGE - CyParameters.EPS)
                        m_errorProvider.SetError(m_cmbxAdjustableVref, string.Empty);
                    else
                        m_errorProvider.SetError(m_cmbxAdjustableVref, Properties.Resources.ERR_VREF_ADJ);
                }
                // if the value is greater than MIN_TAP VOLTAG add to the list
                else if (tapVoltage >= CyParameters.MIN_TAP_VOLTAGE - CyParameters.EPS)
                    m_cmbxAdjustableVref.Items.Add(new CyAdjVref(tapNumber, tapVoltage));
            }

            // if RefType is fixed remove error, the comboBox is available only for Adjastable Vref type
            if (m_params.RefType == CyEnumRefType.FIXED)
                m_errorProvider.SetError(m_cmbxAdjustableVref, string.Empty);

            // select the tap number that was selected before
            // newSelectedComboBoxIndex equals -1 if tab number is greater than MAX_TAP_NUMBER (can be selected in 
            // Expresion View). In this case the expresion view validation will force users select a valide tap number.
            m_cmbxAdjustableVref.SelectedIndex = newSelectedComboBoxIndex;

            // restore SelectedIndexChanged handling 
            m_cmbxAdjustableVref.SelectedIndexChanged += cmbxAdjustableVref_SelectedIndexChanged;
        }

        #endregion Update UI

        #region Event Handlers

        private void radioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rbSender = (RadioButton)sender;

            if (rbSender.Checked == false) return;

            // Vref source
            if (rbSender == rbInternalBandgap)
            {
                m_lblBandgap.Enabled = true;
                numVinref.Enabled = false;
                m_params.RefSource = CyEnumRefSourceType.INTERNAL_BANDGAP;

                ValidateVinref();
                ValidateVbgr();

                m_lblVrangeActual.Text = m_params.VrangeActual.ToString(VOLTAGE_DISPLAY_FORMAT_GUI);
                UpdateVrefComboBoxItems();
            }
            else if (rbSender == rbExternalReference)
            {
                m_lblBandgap.Enabled = false;
                numVinref.Enabled = true;
                m_params.RefSource = CyEnumRefSourceType.EXTERNAL_REFERENCE;

                ValidateVinref();
                ValidateVbgr();

                m_lblVrangeActual.Text = m_params.VrangeActual.ToString(VOLTAGE_DISPLAY_FORMAT_GUI);
                UpdateVrefComboBoxItems();
            }

            // Vref type
            else if (rbSender == rbFixed)
            {
                panelAdjustableVref.Enabled = false;
                m_params.RefType = CyEnumRefType.FIXED;
                UpdateVrefComboBoxItems();
            }
            else if (rbSender == rbAdjustable)
            {
                panelAdjustableVref.Enabled = true;
                m_params.RefType = CyEnumRefType.ADJUSTABLE;
                UpdateVrefComboBoxItems();
            }            

            // not handled radioButton
            else
                Debug.Assert(false);

            ValidateActualVrange();
        }

        private void numeric_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown numSender = (NumericUpDown)sender;

            if (numSender == numVinref)
            {
                m_params.Vinref = Convert.ToDouble(numVinref.Value);

                ValidateVinref();
            }
            else if (numSender == numVrange)
            {
                m_params.VrangeDesired = Convert.ToDouble(numVrange.Value);
            }

            // not handled numericUpDown
            else
                Debug.Assert(false);

            m_lblVrangeActual.Text = m_params.VrangeActual.ToString(VOLTAGE_DISPLAY_FORMAT_GUI);
            UpdateVrefComboBoxItems();
            ValidateActualVrange();
        }

        private void cmbxAdjustableVref_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                m_params.Tap = ((CyAdjVref)m_cmbxAdjustableVref.SelectedItem).TapNumber;
            }
            catch (Exception ex)
            {
                Debug.Fail(ex.Message);
            }

            UpdateVrefComboBoxItems();
        }

        #endregion Event Handlers

        #region Private Methods

        private void ValidateVinref()
        {
            string errMsg;
            double maxVinref;

            if (m_params.RefSource == CyEnumRefSourceType.INTERNAL_BANDGAP)
            {
                m_errorProvider.SetError(numVinref, string.Empty);
                return;
            }

            if (CyParameters.MAX_VINREF_VOLTAGE < m_params.Vdda - CyParameters.MAX_VINREF_VDDA_OFFSET)
            {
                errMsg = Properties.Resources.ERR_VINREF_FORMATSTR2;
                maxVinref = CyParameters.MAX_VINREF_VOLTAGE;
            }
            else
            {
                errMsg = Properties.Resources.ERR_VINREF_VDDA_FORMATSTR2;
                maxVinref = m_params.Vdda - CyParameters.MAX_VINREF_VDDA_OFFSET;
            }

            if (m_params.Vinref < CyParameters.MIN_VINREF_VOLTAGE - CyParameters.EPS || 
                m_params.Vinref > maxVinref + CyParameters.EPS)
            {
                m_errorProvider.SetError(numVinref, string.Format(errMsg,
                    CyParameters.MIN_VINREF_VOLTAGE.ToString(VOLTAGE_DISPLAY_FORMAT_ERRMSG), 
                    maxVinref.ToString(VOLTAGE_DISPLAY_FORMAT_ERRMSG)));
            }
            else
            {
                m_errorProvider.SetError(numVinref, string.Empty); 
            }
        }

        private void ValidateVbgr()
        {
            double maxRange = m_params.Bandgap + CyParameters.MAX_VINREF_VDDA_OFFSET;

            if (m_params.RefSource == CyEnumRefSourceType.INTERNAL_BANDGAP &&
                m_params.Bandgap > m_params.Vdda - CyParameters.MAX_VINREF_VDDA_OFFSET + CyParameters.EPS)
            {
                m_errorProvider.SetError(m_lblBandgap, string.Format(Properties.Resources.ERR_GUI_VBGR_FORMATSTR2,
                    maxRange.ToString(CyTabControlWrapper. VOLTAGE_DISPLAY_FORMAT_ERRMSG), 
                    CyParameters.MAX_VINREF_VDDA_OFFSET.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG)));
            }
            else
            {
                m_errorProvider.SetError(m_lblBandgap, string.Empty); 
            }
        }

        private void ValidateActualVrange()
        {
            if (m_params.RefType == CyEnumRefType.FIXED)
            {
                m_errorProvider.SetError(m_lblVrangeActual, string.Empty);
                return;
            }

            double minRange = m_params.Vsource;
            double maxRange = m_params.Vdda - CyParameters.MAX_VRANGE_VDDA_OFFSET;
            string errMsg = Properties.Resources.ERR_VRANGE_VDDA_FORMATSTR3;

            if (CyParameters.MAX_VRANGE_VOLTAGE < m_params.Vdda - CyParameters.MAX_VRANGE_VDDA_OFFSET)
            {
                errMsg = Properties.Resources.ERR_VRANGE_FORMATSTR3;
                maxRange = CyParameters.MAX_VRANGE_VOLTAGE;
            }
            else
            {
                errMsg = Properties.Resources.ERR_VRANGE_VDDA_FORMATSTR3;
                maxRange = m_params.Vdda - CyParameters.MAX_VRANGE_VDDA_OFFSET;
            }

            if (minRange < maxRange + CyParameters.EPS)
            {
                if (m_params.VrangeActual < minRange - CyParameters.EPS ||
                    m_params.VrangeActual > maxRange + CyParameters.EPS)
                {
                    string sMinRange = minRange.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG);
                    string sMaxRange = maxRange.ToString(CyTabControlWrapper.VOLTAGE_DISPLAY_FORMAT_ERRMSG);

                    m_errorProvider.SetError(m_lblVrangeActual, string.Format(errMsg,
                        sMinRange, sMaxRange, m_params.VsourceName));
                }
                else
                {
                    m_errorProvider.SetError(m_lblVrangeActual, string.Empty);
                }
            }
            else
            {
                m_errorProvider.SetError(m_lblVrangeActual, string.Empty);
            }
        }

        #endregion Private Methods

        #region Internal Types

        private class CyAdjVref
        {
            #region Constructors

            public CyAdjVref(byte tapNumber, double tapVoltage)
            {
                TapVoltage = tapVoltage;
                TapNumber = tapNumber;
            }

            #endregion Constructors

            #region Properties

            public byte TapNumber { get; set; }

            public double TapVoltage { get; set; }

            #endregion Properties
            
            #region Public Methods

            public override string ToString()
            {
                return String.Format(ADJVREF_ITEM_FORMAT2, TapVoltage, TapNumber);
            }

            #endregion Public Methods
        }

        #endregion Internal Types
    }
}
