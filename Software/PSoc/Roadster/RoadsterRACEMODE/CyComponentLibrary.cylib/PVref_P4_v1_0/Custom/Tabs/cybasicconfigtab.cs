/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Diagnostics;


namespace PVref_P4_v1_0.Tabs
{
    public partial class CyBasicConfigTab : CyTabControlWrapper
    {
        #region Class Consts

        public const string REFSOURCE_DISPLAY_FORMAT = "{0:0.00}";
        public const string VREF_DISPLAY_FORMAT = "{0:0.00}";

        #endregion Class Consts

        #region CyTabControlWrapper Override

        public override string TabName
        {
            get { return CyCustomizer.BASIC_TAB_NAME; }
        }

        #endregion CyTabControlWrapper Override

        #region Constructors

        public CyBasicConfigTab(CyParameters param)
            : base(param)
        {
            m_params = param;

            InitializeComponent();

            m_cmbxVref.Items.Clear();
            for (int i = 0; i < CyParameters.MAX_DIVIDER_VALUE; i++)
                m_cmbxVref.Items.Add(string.Empty);

            UpdateUiFromTable();
        }

        #endregion Constructors

        #region Update UI

        public void UpdateUiFromTable()
        {
            m_rbRefSourceBandgap.Checked = CyEnumRefSourceType.Bandgap == m_params.RefSource;
            m_rbRefSourceVdda.Checked = CyEnumRefSourceType.Vdda == m_params.RefSource;

            m_labelRefSourceVdda.Text = string.Format(REFSOURCE_DISPLAY_FORMAT, m_params.Vdda);
            m_labelRefSourceBandgap.Text = string.Format(REFSOURCE_DISPLAY_FORMAT, m_params.Bandgap);

            if (m_cmbxVref.Items.Count > CyParameters.MAX_DIVIDER_VALUE - m_params.SelOutputVoltage)
                m_cmbxVref.SelectedIndex = CyParameters.MAX_DIVIDER_VALUE - m_params.SelOutputVoltage;
            else
                Debug.Assert(false);

            UpdateVrefComboBoxItems();
            UpdatePictureLabels();
        }

        private void UpdatePictureLabels()
        {
            string refSourceName = m_params.GetSelectedRefSourceName();
            double refSourceValue = m_params.GetSelectedRefSourceValue();

            m_labelPictureRefSource.Text = string.Format("{0}{1}{2} V", refSourceName, Environment.NewLine,
                string.Format(REFSOURCE_DISPLAY_FORMAT, refSourceValue));
            m_labelPictureVref.Text = string.Format("{0}{1}{2} V", CyParameters.VREF_NAME, Environment.NewLine,
                string.Format(VREF_DISPLAY_FORMAT, m_params.GetVref()));
        }

        private void UpdateVrefComboBoxItems()
        {
            Debug.Assert(m_cmbxVref.Items.Count == CyParameters.MAX_DIVIDER_VALUE);

            double refSourceValue = m_params.GetSelectedRefSourceValue();
            for (int i = CyParameters.MAX_DIVIDER_VALUE; i > 0; i--)
            {
                m_cmbxVref.Items[CyParameters.MAX_DIVIDER_VALUE - i] = String.Format(VREF_DISPLAY_FORMAT + " (tap {1})",
                    (refSourceValue / CyParameters.MAX_DIVIDER_VALUE) * i, i);
            }
        }

        #endregion Update UI

        #region Event Handlers

        private void cmbVref_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.SelOutputVoltage = (byte)(CyParameters.MAX_DIVIDER_VALUE - m_cmbxVref.SelectedIndex);
            UpdatePictureLabels();
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rbSender = (RadioButton)sender;

            if (!rbSender.Checked)
                return;

            if (rbSender == m_rbRefSourceBandgap)
            {
                m_params.RefSource = CyEnumRefSourceType.Bandgap;
            }
            else if (rbSender == m_rbRefSourceVdda)
            {
                m_params.RefSource = CyEnumRefSourceType.Vdda;
            }
            else
            {
                Debug.Assert(false);
            }

            UpdateVrefComboBoxItems();
            UpdatePictureLabels();
        }

        #endregion Event Handlers
    }
}
