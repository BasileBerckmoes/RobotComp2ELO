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
using CyDesigner.Extensions.Common;

namespace USBFS_v3_20
{
    public partial class CyAdvancedPage : CyEditingWrapperControl
    {
        public CyAdvancedPage()
        {
            InitializeComponent();
        }

        public CyAdvancedPage(CyUSBFSParameters parameters)
            : base(parameters)
        {
            InitializeComponent();
            InitFields();
        }

        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_ADVANCED; }
        }

        private List<CyCustErr> GetErrors(ControlCollection controlCollect, List<CyCustErr> errorList)
        {
            string errorMessage = string.Empty;

            foreach (Control control in controlCollect)
            {
                errorMessage = errProvider.GetError(control);
                if (string.IsNullOrEmpty(errorMessage) == false)
                    errorList.Add(new CyCustErr(errorMessage));

                GetErrors(control.Controls, errorList);
            }

            return errorList;
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (errProvider != null)
            {
                // Check controls for errors
                GetErrors(this.Controls, errorList);
            }

            return errorList;
        }
        #endregion

        public void InitFields()
        {
            checkBoxExtClass.Checked = m_parameters.Extern_cls;
            checkBoxExtVendor.Checked = m_parameters.Extern_vnd;
            checkBoxVBusMon.Checked = m_parameters.Mon_vbus;
            checkBoxSofOutput.Checked = m_parameters.Out_sof;
            checkBoxSofInterrupt.Checked = m_parameters.EnableSofInterrupt;
            checkBox16BitEpApi.Checked = m_parameters.Gen16bitEpAccessApi;
            checkBoxBattChargDetect.Checked = m_parameters.EnableBattChargDetect;

            radioButtonVbusPoweredPad.Checked = m_parameters.PowerPad_vbus;
            if (!m_parameters.PowerPad_vbus)
            {
                radioButtonVbusInternal.Checked = !m_parameters.Extern_vbus;
                radioButtonVbusExternal.Checked = m_parameters.Extern_vbus;
            }

            CheckBattChargDetectConfig();
            CheckVbusPowerPadConfig();
            UpdateCheckBox16BitEpApiVisibility();

            m_gbxVbusMonitoring.Enabled = checkBoxVBusMon.Checked;
        }

        private void UpdateCheckBox16BitEpApiVisibility()
        {
            checkBox16BitEpApi.Visible = m_parameters.IsPSoC4AL_IpBlock;
        }

        private void CheckVbusPowerPadConfig()
        {
            if (!m_parameters.IsPSoC4AL_IpBlock)
            {
                if (radioButtonVbusPoweredPad.Checked && checkBoxVBusMon.Checked)
                {
                    radioButtonVbusPoweredPad.Enabled = true;
                    errProvider.SetError(radioButtonVbusPoweredPad, Properties.Resources.ERR_VBUS_POWER_PAD_DEVICE);
                }
                else
                {
                    radioButtonVbusPoweredPad.Enabled = false;
                    errProvider.SetError(radioButtonVbusPoweredPad, string.Empty);
                }
            }
        }

        private void CheckBattChargDetectConfig()
        {
            if (m_parameters.IsPSoC4AL_IpBlock)
            {
                if (checkBoxBattChargDetect.Checked)
                {
                    if (!checkBoxVBusMon.Checked)
                        wrgProvider.SetError(checkBoxBattChargDetect, Properties.Resources.WRG_DRC_BATT_CHARG_DETECT_CONFIG);
                    else
                        wrgProvider.SetError(checkBoxBattChargDetect, string.Empty);
                }
                else
                    wrgProvider.SetError(checkBoxBattChargDetect, string.Empty);
            }
            else
            {
                if (checkBoxBattChargDetect.Checked)
                {
                    checkBoxBattChargDetect.Enabled = true;
                    errProvider.SetError(checkBoxBattChargDetect, Properties.Resources.ERR_BATT_CHARG_DETECT_DEVICE);
                }
                else
                {
                    checkBoxBattChargDetect.Enabled = false;
                    errProvider.SetError(checkBoxBattChargDetect, string.Empty);
                }
            }
        }

        private void checkBoxExtClass_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == checkBoxExtClass)
            {
                m_parameters.Extern_cls = ((CheckBox)sender).Checked;
            }
            else if (sender == checkBoxExtVendor)
            {
                m_parameters.Extern_vnd = ((CheckBox)sender).Checked;
            }
            else if (sender == checkBoxVBusMon)
            {
                m_parameters.Mon_vbus = ((CheckBox)sender).Checked;
                m_gbxVbusMonitoring.Enabled = checkBoxVBusMon.Checked;

                CheckVbusPowerPadConfig();
                CheckBattChargDetectConfig(); 
            }
            else if (sender == checkBoxSofOutput)
            {
                m_parameters.Out_sof = ((CheckBox)sender).Checked;
            }
            else if(sender == checkBoxSofInterrupt)
            {
                m_parameters.EnableSofInterrupt = ((CheckBox)sender).Checked;
                m_parameters.InterrPage.UpdateInterruptsTableView();
            }
            else if (sender == checkBox16BitEpApi)
            {
                m_parameters.Gen16bitEpAccessApi = ((CheckBox)sender).Checked;
            }
            else if (sender == checkBoxBattChargDetect)
            {
                m_parameters.EnableBattChargDetect = ((CheckBox)sender).Checked;

                CheckBattChargDetectConfig();
            }
        }

        private void radioButtonVbus_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            m_parameters.PowerPad_vbus = (rb == radioButtonVbusPoweredPad);
            m_parameters.Extern_vbus = (rb == radioButtonVbusExternal);
            CheckBattChargDetectConfig();
            CheckVbusPowerPadConfig();
        }
    }
}
