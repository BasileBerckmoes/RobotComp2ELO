/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace SMBusSlave_v5_20
{
    public partial class CyGeneralTab : CyTabWrapper
    {
        private readonly ICyTerminalQuery_v1 m_termQuery;

        #region CyTabControlWrapper members
        public override string TabName
        {
            get { return "General"; }
        }
        #endregion

        #region Constructor(s)
        public CyGeneralTab(CyParameters parameters, ICyTerminalQuery_v1 termQuery)
            : base(parameters)
        {
            m_params.GeneralTab = this;
            m_termQuery = termQuery;
            InitializeComponent();

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip;

            // Initialize toolstrip
            cyToolStrip.m_params = parameters;

            // Initialize comboboxes
            cbMode.DataSource = m_params.m_modeList.ToArray();

            SetSmbAlertEnabling(m_params.EnableSmbAlertPin);

            numPagedCommands.Maximum = UInt16.MaxValue;
            numPagedCommands.TextChanged += new EventHandler(numPagedCommands_TextChanged);
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            bool prevGlobalEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            cbMode.SelectedItem = CyDictParser.GetDictValue(m_params.m_dnDict, m_params.Mode);
            cbDataRate.Text = m_params.DataRate.ToString();
            UpdateDataRateAppearance();
            UpdateActualDataRateLabel();

            tbSlaveAddress.Text = m_params.Hex ? CyParameters.CellConvertHex(m_params.SlaveAddress) : 
                                                 m_params.SlaveAddress.ToString();

            chbEnablePec.Checked = m_params.EnablePec;

            chbEnableSmbAlertPin.Checked = m_params.EnableSmbAlertPin;
            if (m_params.SmbAlertMode == CyESmbAlertModeType.MODE_AUTO)
                rbAutoMode.Checked = true;
            else
                rbManualMode.Checked = true;
            numPagedCommands.Text = m_params.PagedCommands.ToString();
            chbEnableReceiveByteProtocol.Checked = m_params.EnableRecieveByteProtocol;
            chbSupportPageCmd.Checked = m_params.SupportPageCmd;
            chbSupportQueryCmd.Checked = m_params.SupportQueryCmd;

            m_params.GlobalEditMode = prevGlobalEditMode;
        }
        #endregion

        #region Data rate control initialization
        private void InitializeDataRateControl(CyEModeSelType mode)
        {
            List<UInt16> availableValues;
            string dataRateText = cbDataRate.Text;

            if (mode == CyEModeSelType.PMBUS_SLAVE)
            {
                UInt16 dataRateValue;
                if (UInt16.TryParse(dataRateText, out dataRateValue))
                {
                    if (CyParameters.pmBusDataRateList.Contains(dataRateValue) == false)
                    {
                        availableValues = new List<UInt16>(CyParameters.pmBusDataRateList);
                        m_errorProvider.SetError(cbDataRate, string.Format(Resources.DataRateOutOfRange,
                            availableValues[0], availableValues[1]));
                        availableValues.Add(dataRateValue);
                    }
                    else
                    {
                        availableValues = new List<UInt16>(CyParameters.pmBusDataRateList);
                        m_errorProvider.SetError(cbDataRate, string.Empty);
                    }
                }
                else
                {
                    availableValues = new List<UInt16>(CyParameters.pmBusDataRateList);
                }
            }
            else
            {
                availableValues = new List<UInt16>(CyParameters.smBusDataRateList);
            }

            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            cbDataRate.Items.Clear();
            foreach (UInt16 item in availableValues)
            {
                cbDataRate.Items.Add(item);
            }
            cbDataRate.Text = dataRateText;
            m_params.GlobalEditMode = prevGEM;
        }

        private void UpdateDataRateAppearance()
        {
            if ((m_params.Implementation == CyEImplementationType.I2C__UDB && m_params.UdbInternalClock == false) ||
                (m_params.IsPSoC4 && m_params.ClockFromTerm))
            {
                lblDataRate.Enabled = false;
                cbDataRate.Enabled = false;
            }
            else
            {
                lblDataRate.Enabled = true;
                cbDataRate.Enabled = true;
            }
        }

        private void UpdateActualDataRateLabel()
        {
            lblActualDataRateValue.Text = CyDividerCalculator.GetActualDataRateCalculatorLabel(m_params, m_termQuery);
        }

        public void UpdateClockDependencies()
        {
            UpdateDataRateAppearance();
            UpdateActualDataRateLabel();
        }
        #endregion

        #region Event handlers
        private void cbMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEModeSelType selectedMode = (CyEModeSelType)CyDictParser.GetDictKey(m_params.m_dnDict,
                cbMode.SelectedItem.ToString());
            m_params.Mode = selectedMode;
            InitializeDataRateControl(selectedMode);
            bool visibility = (selectedMode == CyEModeSelType.SMBUS_SLAVE);
            gbSmBus.Visible = visibility;
            if (m_params.GlobalEditMode)
            {
                m_params.PmBusCmdsTab.SetPMBusCmdsTabVisibility(selectedMode);
                m_params.CustomCmdsTab.SetPageVisibility();
                m_params.CustomCmdsTab.SetQueryVisibility();
                m_params.PmBusCmdsTab.ValidateCodes();
                m_params.CustomCmdsTab.ValidateCodes();
                m_params.CustomCmdsTab.ValidateNames();
            }
        }

        private void cbDataRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            // If data rate value is invalid for current mode, than remove combobox item and error provider message
            if (m_params.GlobalEditMode)
            {
                if (m_errorProvider.GetError((ComboBox) sender) != string.Empty)
                {
                    string dataRateText = cbDataRate.Text;
                    m_errorProvider.SetError((ComboBox) sender, string.Empty);
                    UInt16 dataRateValue;
                    if (UInt16.TryParse(((ComboBox) sender).Text, out dataRateValue))
                    {
                        cbDataRate.Items.Clear();
                        foreach (UInt16 item in CyParameters.pmBusDataRateList)
                        {
                            cbDataRate.Items.Add(item);
                        }
                        cbDataRate.Text = dataRateText;
                    }
                }
                m_params.DataRate = Convert.ToUInt16(cbDataRate.Text);
                UpdateActualDataRateLabel();
                m_params.UpdateTimeout();
            }
        }

        private void numPagedCommands_TextChanged(object sender, EventArgs e)
        {
            if (UpdateErrorProvider(sender, numPagedCommands.Text, CyParamRange.PAGED_CMDS_MIN,
                CyParamRange.PAGED_CMDS_MAX, Resources.PagedCmdsOutOfRange))
            {
                m_params.PagedCommands = Convert.ToByte(numPagedCommands.Text);
                
                // Validate Custom Commands tab
                if (m_params.CustomCmdsTab != null && m_params.GlobalEditMode)
                {
                    m_params.CustomCmdsTab.ValidateAllTable();
                }
            }
        }

        private void chbEnablePec_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnablePec = chbEnablePec.Checked;
        }

        private void chbEnableSmbAlertPin_CheckedChanged(object sender, EventArgs e)
        {
            bool choise = ((CheckBox)sender).Checked;
            m_params.EnableSmbAlertPin = choise;
            SetSmbAlertEnabling(choise);

            UpdateSmbAlertErrorProvider();
        }

        private void rbAutoMode_CheckedChanged(object sender, EventArgs e)
        {
            m_params.SmbAlertMode = (((RadioButton)sender).Checked) ?
                CyESmbAlertModeType.MODE_AUTO : CyESmbAlertModeType.MODE_MANUAL;
        }

        private void chbEnableRecieveByteProtocol_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableRecieveByteProtocol = ((CheckBox)sender).Checked;
        }

        private void chbSupportPageCmd_CheckedChanged(object sender, EventArgs e)
        {
            bool isChecked = ((CheckBox)sender).Checked;
            m_params.SupportPageCmd = isChecked;

            m_params.CustomCmdsTab.SetPageVisibility();
        }

        private void chbSupportQueryCmd_CheckedChanged(object sender, EventArgs e)
        {
            bool isChecked = ((CheckBox)sender).Checked;
            m_params.SupportQueryCmd = isChecked;

            m_params.CustomCmdsTab.SetQueryVisibility();
        }

        private void tbSlaveAddress_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode == false) return;

            byte? slaveAddress;
            string message;
            bool isHex = CyParameters.IsHex(tbSlaveAddress.Text);

            if (isHex)
            {
                slaveAddress = CyParameters.ParseNullableHexByte(tbSlaveAddress.Text.Replace("0x", string.Empty));
            }
            else
            {
                try
                {
                    slaveAddress = Convert.ToByte(tbSlaveAddress.Text);
                }
                catch (Exception)
                {
                    slaveAddress = null;
                }
            }

            if (slaveAddress == null ||
                slaveAddress < CyParamRange.SLAVE_ADDRESS_MIN || slaveAddress > CyParamRange.SLAVE_ADDRESS_MAX)
            {
                if (isHex)
                {
                    message = string.Format(Resources.SlaveAddressOutOfRange,
                        CyParameters.CellConvertHex(CyParamRange.SLAVE_ADDRESS_MIN),
                        CyParameters.CellConvertHex(CyParamRange.SLAVE_ADDRESS_MAX));
                }
                else
                {
                    message = string.Format(Resources.SlaveAddressOutOfRange, CyParamRange.SLAVE_ADDRESS_MIN,
                        CyParamRange.SLAVE_ADDRESS_MAX);
                }
                m_errorProvider.SetError((Control)sender, message);
            }
            else
            {
                if (CyParameters.reservedSMBusAddresses.Contains(slaveAddress.Value))
                    m_errorProvider.SetError((Control)sender, Resources.ReservedSMBusAddress);
                else
                    m_errorProvider.SetError((Control)sender, string.Empty);
            }

            if (slaveAddress.HasValue)
            {
                m_params.Hex = isHex;
                m_params.SlaveAddress = slaveAddress.Value;
            }
        }

        private void CyGeneralTab_Load(object sender, EventArgs e)
        {
            m_params.UpdateClock(m_params.InstQuery, m_termQuery);
        }
        #endregion

        #region SmbAlert handling
        public void UpdateSmbAlertErrorProvider()
        {
            if (m_params.EnableSmbAlertPin && m_params.AddressDecode == CyEAddressDecodeType.I2C__Hardware &&
                m_params.IsPSoC4 == false)
            {
                m_errorProvider.SetError(chbEnableSmbAlertPin, string.Format(Resources.EnableSmbAlertError,
                    Resources.I2cConfTabDisplayName));
            }
            else
                m_errorProvider.SetError(chbEnableSmbAlertPin, string.Empty);
        }

        private void SetSmbAlertEnabling(bool enabled)
        {
            rbAutoMode.Enabled = enabled;
            rbManualMode.Enabled = enabled;
        }
        #endregion
    }
}
