/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;

namespace Bootloader_v1_50
{
    public partial class CyGeneralPage : CyEditingWrapperControl
    {
        enum CyPacketChecksumType { BASIC_SUM, CRC_16 };

        #region Const
        const uint MIN_VAL = 0;
        const uint MAX_VAL_16 = 0xFFFF;
        const string MAX_VAL_16_STR = "0xFFFF";
        const uint MAX_VAL_WAITTIME = 255;
        const int WAIT_TIME_MULTIPLIER = 100;
        #endregion Const

        List<string> m_communicationComponentList = new List<string>();
        int m_launcherIndex = -1;
        bool m_launcherDialogShown = false;
        bool m_copierDialogShown = false;

        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructors
        public CyGeneralPage()
        {
            InitializeComponent();
        }

        public CyGeneralPage(CyParameters parameters)
            :base(parameters)
        {
            InitializeComponent();

            numUpDownWaitTime.TextChanged += numUpDownWaitTime_TextChanged;
            // DPI-independent fix to match checkbox and label text
            labelMultiApp.Left = checkBoxMultiApp.Right - labelMultiApp.Width - 3;

            InitFields();
        }
        #endregion Constructors

        #region Initialization
        public void InitFields()
        {
            m_parameters.KeyArray.DeserializeKey();

            checkBoxWaitTime.Checked = m_parameters.WaitEnable;
            numUpDownWaitTime.Value = m_parameters.WaitTime * WAIT_TIME_MULTIPLIER;
            textBoxVersion.Text = CyUtils.HEX_PREFIX + m_parameters.Version.ToString("X4");

            comboBoxPktChecksumType.SelectedIndex = m_parameters.PacketChecksumType ?
                    (byte)CyPacketChecksumType.CRC_16 : (byte)CyPacketChecksumType.BASIC_SUM;

            checkBoxBeAppValidation.Checked = m_parameters.FastValidation;
            checkBoxBrAppValidation.Checked = m_parameters.FastBrValidation;

            checkBoxSecurityKey.Checked = m_parameters.SecurityKeyAvail;
            foreach (Control ctrl in panelSecurityKey.Controls)
            {
                TextBox tb = ctrl as TextBox;
                if (tb != null)
                {
                    int byteNum = Convert.ToInt32(tb.Tag);
                    if (byteNum < m_parameters.SecurityKeyLength)
                        tb.Text = m_parameters.KeyArray[byteNum].ToString("X2");
                    else
                        tb.Enabled = false;
                }
            }

            checkBoxCommSize.Checked = m_parameters.CmdFlashSize;
            checkBoxCommVerify.Checked = m_parameters.CmdVerifyRowInFlash;
            checkBoxCommErase.Checked = m_parameters.CmdEraseRow;
            checkBoxCommRowChksum.Checked = m_parameters.CmdVerifyRow;
            checkBoxCommAppChksum.Checked = m_parameters.CmdVerifyAppChksum;
            checkBoxCommSend.Checked = m_parameters.CmdSendData;
            checkBoxCommSync.Checked = m_parameters.CmdSyncBootloader;
            checkBoxCommStatus.Checked = m_parameters.CmdGetAppStatus;
            checkBoxCommMetadata.Checked = m_parameters.CmdGetMetadata;

            checkBoxMultiApp.Checked = m_parameters.MultiAppBootloader;

            checkBoxGoldenImage.Checked = m_parameters.GoldenImageSupport;
            checkBoxAutoAppSwitch.Checked = m_parameters.AutoAppSwitching;
            checkBoxCopier.Checked = m_parameters.Copier;

            m_communicationComponentList = new List<string>();
            m_communicationComponentList.Add(CyParameters.CUSTOM_INTERFACE);
            try
            {
                m_communicationComponentList.AddRange(
                    m_parameters.InstQuery.DesignQuery.GetBootloaderCommunicationComponents());
            }
            catch
            {
                Debug.Assert(false);
            }
            // Support deselection of launcher item when not supported
            if ((m_parameters.IsLauncherSupported == true) || (m_parameters.Launcher == true))
            {
                m_communicationComponentList.Add(CyParameters.LAUNCHER_ONLY);
                m_launcherIndex = m_communicationComponentList.Count - 1;
            }

            comboBoxIOComponent.Items.Clear();
            comboBoxIOComponent.Items.AddRange(m_communicationComponentList.ToArray());

            if (m_parameters.Launcher == true)
            {
                comboBoxIOComponent.SelectedIndex = m_launcherIndex;
            }
            else if (comboBoxIOComponent.Items.Contains(m_parameters.IOComponent))
            {
                comboBoxIOComponent.SelectedItem = m_parameters.IOComponent;
            }
            else
            {
                comboBoxIOComponent.SelectedIndex = 0;
            }
        }

        public void CyGeneralPage_Load(object sender, EventArgs e)
        {
            // Update IOComponent parameter when selected communication component
            // was removed from the schematic
            if ((comboBoxIOComponent.SelectedIndex >= 0) &&
                (comboBoxIOComponent.Text != m_parameters.IOComponent))
            {
                m_parameters.IOComponent = comboBoxIOComponent.Text;
            }
        }
        #endregion Initialization

        #region Event handlers

        private void textBoxVersion_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            uint val;
            if (!CyUtils.IsHex(tb.Text))
            {
                errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBFormat, 2));
            }
            else
            {
                if (CyUtils.TryParseHex(tb.Text, out val))
                {
                    if (!CyUtils.CheckRange(val, MIN_VAL, MAX_VAL_16))
                    {
                        errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange,
                                                               MIN_VAL, MAX_VAL_16_STR));
                    }
                    else
                    {
                        errProvider.SetError(tb, String.Empty);
                        m_parameters.Version = (UInt16)val;
                    }
                }
                else
                {
                    errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange, MIN_VAL, MAX_VAL_16_STR));
                }
            }
        }

        private void checkBoxOptions_CheckedChanged(object sender, EventArgs e)
        {
            bool val = ((CheckBox)sender).Checked;
            if (sender == checkBoxBeAppValidation)
                m_parameters.FastValidation = val;
            if (sender == checkBoxBrAppValidation)
                m_parameters.FastBrValidation = val;
        }

        private void checkBoxComm_CheckedChanged(object sender, EventArgs e)
        {
            bool val = ((CheckBox)sender).Checked;
            if (sender == checkBoxCommSize)
                m_parameters.CmdFlashSize = val;
            else if (sender == checkBoxCommVerify)
                m_parameters.CmdVerifyRowInFlash = val;
            else if (sender == checkBoxCommErase)
                m_parameters.CmdEraseRow = val;
            else if (sender == checkBoxCommRowChksum)
                m_parameters.CmdVerifyRow = val;
            else if (sender == checkBoxCommAppChksum)
                m_parameters.CmdVerifyAppChksum = val;
            else if (sender == checkBoxCommSend)
                m_parameters.CmdSendData = val;
            else if (sender == checkBoxCommSync)
                m_parameters.CmdSyncBootloader = val;
            else if (sender == checkBoxCommStatus)
                m_parameters.CmdGetAppStatus = val;
            else if (sender == checkBoxCommMetadata)
                m_parameters.CmdGetMetadata = val;
        }

        private void checkBoxWaitTime_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.WaitEnable = checkBoxWaitTime.Checked;
            UpdateEnabledState();
        }

        private void comboBoxPktChecksumType_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool res = false;
            if (comboBoxPktChecksumType.SelectedIndex == (byte)CyPacketChecksumType.CRC_16)
                res = true;
            m_parameters.PacketChecksumType = res;
        }

        private void numUpDownWaitTime_ValueChanged(object sender, EventArgs e)
        {
            m_parameters.WaitTime = (byte)((int)numUpDownWaitTime.Value / WAIT_TIME_MULTIPLIER);
        }

        private void numUpDownWaitTime_TextChanged(object sender, EventArgs e)
        {
            // Get value from control
            UInt16? waitTimeValue = CyUtils.ConvertStrToUInt16(numUpDownWaitTime.Text);

            // Update error provider
            bool noErrors = UpdateWaitTimeErrProvider(waitTimeValue);

            if (noErrors)
            {
                m_parameters.WaitTime = (byte)(waitTimeValue.Value / WAIT_TIME_MULTIPLIER);
            }
        }

        private void checkBoxMultiApp_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.MultiAppBootloader = checkBoxMultiApp.Checked;
            UpdateEnabledState();
        }

        private void comboBoxIOComponent_SelectedIndexChanged(object sender, EventArgs e)
        {
            string errMsg = String.Empty;

            if ((m_launcherIndex >= 0) && 
                (comboBoxIOComponent.SelectedIndex == m_launcherIndex))
            {
                if (!m_parameters.IsLauncherSupported)
                {
                    errMsg = Properties.Resources.LauncherUnsupported;
                }
                if ((m_parameters.Launcher == false) && (m_launcherDialogShown == false))
                {
                    MessageBox.Show(Properties.Resources.LauncherDialog,
                        Properties.Resources.LauncherDialogCaption,
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                    m_launcherDialogShown = true;
                }
                m_parameters.Launcher = true;
                checkBoxMultiApp.Checked = true;
            }
            else
            {
                if ((m_launcherIndex >= 0) && (!m_parameters.IsLauncherSupported))
                {
                    comboBoxIOComponent.Items.RemoveAt(m_launcherIndex);
                    m_launcherIndex = -1;
                }
                m_parameters.Launcher = false;
            }
            m_parameters.IOComponent = comboBoxIOComponent.Text;

            errProvider.SetError(comboBoxIOComponent, errMsg);
            UpdateEnabledState();
        }

        private void checkBoxGoldenImage_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.GoldenImageSupport = checkBoxGoldenImage.Checked;
        }

        private void checkBoxAutoAppSwitch_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.AutoAppSwitching = checkBoxAutoAppSwitch.Checked;
        }

        private void checkBoxCopier_CheckedChanged(object sender, EventArgs e)
        {
            // Show dialog on false->true transition (only once per session)
            if ((checkBoxCopier.Checked == true) &&
                (m_parameters.Copier == false) &&
                (m_copierDialogShown == false))
            {
                MessageBox.Show(Properties.Resources.CopierDialog,
                    Properties.Resources.CopierDialogCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                m_copierDialogShown = true;
            }
            m_parameters.Copier = checkBoxCopier.Checked;
        }

        private void checkBoxSecurityKey_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.SecurityKeyAvail = checkBoxSecurityKey.Checked;
            UpdateEnabledState();
        }

        private void textBoxKeyByte_KeyPress(object sender, KeyPressEventArgs e)
        {
            char c = e.KeyChar;
            if (char.IsControl(c))
                return;
            if ((c >= '0') && (c <= '9'))
                return;
            if ((c >= 'a') && (c <= 'f'))
            {
                e.KeyChar = char.ToUpperInvariant(c);
                return;
            }
            if ((c >= 'A') && (c <= 'F'))
                return;
            // forbid other characters
            e.Handled = true;
        }

        private void textBoxKeyByte_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            string byteStr = tb.Text;

            byte byteVal;
            if (!CyUtils.TryParseHexByte(byteStr, out byteVal))
            {
                return;
            }
            int byteNum = Convert.ToInt32(tb.Tag);
            m_parameters.KeyArray[byteNum] = byteVal;
            if (byteStr.Length == 2)
            {
                SelectNextControl(tb, true, true, true, false);
            }
        }

        private void textBoxKeyByte_Leave(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            int byteNum = Convert.ToInt32(tb.Tag);
            byte byteVal = m_parameters.KeyArray[byteNum];
            tb.Text = byteVal.ToString("X2");
        }
        #endregion Event handlers

        #region Service functions
        private bool UpdateWaitTimeErrProvider(UInt16? value)
        {
            if ((value == null) || (value > CyParameters.MAX_WAIT_TIME))
            {
                errProvider.SetError(numUpDownWaitTime, string.Format(Properties.Resources.ErrTBRange, 0, 
                    CyParameters.MAX_WAIT_TIME));
            }
            else if (value % WAIT_TIME_MULTIPLIER != 0)
            {
                errProvider.SetError(numUpDownWaitTime, Properties.Resources.ErrWaitTime10x);
            }
            else
            {
                errProvider.SetError(numUpDownWaitTime, string.Empty);
            }
            return String.IsNullOrEmpty(errProvider.GetError(numUpDownWaitTime));
        }

        private void UpdateEnabledState()
        {
            bool isLauncherType = (comboBoxIOComponent.SelectedIndex == m_launcherIndex);
            bool isMultiAppType = checkBoxMultiApp.Checked && (!isLauncherType);

            checkBoxMultiApp.Enabled = !isLauncherType;
            labelMultiApp.Visible = isLauncherType;

            checkBoxCommStatus.Enabled = isMultiAppType;
            checkBoxGoldenImage.Enabled = isMultiAppType;
            checkBoxAutoAppSwitch.Enabled = isMultiAppType;
            checkBoxCopier.Enabled = isLauncherType;

            checkBoxWaitTime.Enabled = !isLauncherType;
            labelWaitTime.Enabled = (!isLauncherType) && checkBoxWaitTime.Checked;
            numUpDownWaitTime.Enabled = (!isLauncherType) && checkBoxWaitTime.Checked;
            labelZero.Enabled = (!isLauncherType) && checkBoxWaitTime.Checked;
            labelVersion.Enabled = !isLauncherType;
            textBoxVersion.Enabled = !isLauncherType;
            labelPktChecksumType.Enabled = !isLauncherType;
            comboBoxPktChecksumType.Enabled = !isLauncherType;
            checkBoxSecurityKey.Enabled = !isLauncherType;
            panelSecurityKey.Enabled = (!isLauncherType) && checkBoxSecurityKey.Checked;
            groupBoxCommands.Enabled = !isLauncherType;
        }
        #endregion Service functions

        #region GetErrors() override
        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            errorList.AddRange(base.GetErrors());
            errorList.AddRange(CheckControlsForErrors(this.Controls));
            return errorList;
        }

        protected virtual List<CyCustErr> CheckControlsForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            if (errProvider != null)
            {
                foreach (Control control in controls)
                {
                    errorMessage = errProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                    // Recursively call itself again to make sure that nested controls don't contain errors
                    if (control.Controls.Count > 0)
                        errs.AddRange(CheckControlsForErrors(control.Controls));
                }
            }
            return errs;
        }
        #endregion GetErrors() override
    }
}
