/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace SCB_P4_v4_0
{
    public partial class CySPIPinsTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return "SPI Pins";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.SPIPinsTabDisplayName; }
        }

        #endregion

        public CySPIPinsTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            InitializeComponent();

            m_chbShowTerminals.CheckedChanged += m_chb_CheckedChanged;

            m_chbRemoveSclk.CheckedChanged += m_chb_CheckedChanged;
            m_chbRemoveMosi.CheckedChanged += m_chb_CheckedChanged;
            m_chbRemoveMiso.CheckedChanged += m_chb_CheckedChanged;

            m_params.ScbModeChanged += m_params_ScbModeChanged;

            m_params.SpiModeChanged += delegate
            {
                UpdatePinRemoveState();
            };
        }

        #region Assigning parameters values to controls

        public override void UpdateUI()
        {
            m_chbShowTerminals.Checked = m_params.SPI_SmartioEnable;

            m_chbRemoveSclk.Checked = m_params.SPI_RemoveSclk;
            m_chbRemoveMosi.Checked = m_params.SPI_RemoveMosi;
            m_chbRemoveMiso.Checked = m_params.SPI_RemoveMiso;

            UpdatePinRemoveState();
        }

        #endregion

        #region Event handlers

        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.SPI)
                ShowTab();
            else
                HideTab();
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_chbShowTerminals)
            {
                m_params.SPI_SmartioEnable = m_chbShowTerminals.Checked;
            }
            else if (sender == m_chbRemoveSclk)
            {
                UpdatePinConfig(sender as Control);
                m_params.SPI_RemoveSclk = m_chbRemoveSclk.Checked;
                m_params.OnSpiPinsStateChanged(sender, e);
            }
            else if (sender == m_chbRemoveMosi)
            {
                UpdatePinConfig(sender as Control);
                m_params.SPI_RemoveMosi = m_chbRemoveMosi.Checked;
                m_params.OnSpiPinsStateChanged(sender, e);
            }
            else if (sender == m_chbRemoveMiso)
            {
                UpdatePinConfig(sender as Control);
                m_params.SPI_RemoveMiso = m_chbRemoveMiso.Checked;
                m_params.OnSpiPinsStateChanged(sender, e); 
            }
        }
        #endregion

        #region Update controls state

        private void UpdatePinRemoveState()
        {
            m_chbRemoveSclk.Enabled = m_params.SpiMode.Value != CyESPIModeType.SPI_SLAVE;
            if (m_params.GlobalEditMode && m_chbRemoveSclk.Checked && m_chbRemoveSclk.Enabled == false)
                m_chbRemoveSclk.Checked = false;
        }

        private void UpdatePinConfig(Control control)
        {
            if (m_params.GlobalEditMode) // do not run the method when in expression view
            {
                if (m_chbRemoveMiso.Checked && m_chbRemoveMosi.Checked &&
                    m_chbRemoveSclk.Checked && m_params.SPI_NumberOfSSLines == 0)
                {
                    MessageBox.Show(Resources.SpiRemoveAllPinsNote, Resources.OperationNotAllowedTitle,
                         MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);

                    CheckBox chbBox = control as CheckBox;
                    if (chbBox != null)
                    {
                        chbBox.Checked = false;
                    }
                    else
                    {
                        Debug.Fail("The control isn't a CheckBox.");
                    }
                }
            }
        }
        #endregion

    }
}
