/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ADC_DelSig_v3_20
{
    public partial class CyCommonTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "Basic";
            }
        }
        #endregion

        #region Constructor(s)
        public CyCommonTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();
            InitUI();
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            m_cbNumConfig.Text = m_params.NumConfigurations.ToString();

            switch (m_params.ClockSourceType)
            {
                case CyEClockSource.Internal:
                    m_rbInternal.Checked = true;
                    break;
                case CyEClockSource.External:
                    m_rbExternal.Checked = true;
                    break;
            }

            switch (m_params.InputModeType)
            {
                case CyEInputMode.Single_Mode:
                    m_rbSingleEnded.Checked = true;
                    break;
                case CyEInputMode.Differential_Mode:
                    m_rbDiff.Checked = true;
                    break;
            }

            m_chbSOC.Checked = m_params.UseTriggeredSamplingMode;
            m_chbEnVrefVssa.Checked = m_params.EnableVrefVssa;
            m_chbEnModInput.Checked = m_params.EnableModulatorInput;
        }

        private void InitUI()
        {
            for (int i = CyParamRanges.NUM_MIN_CONFIG; i <= CyParamRanges.NUM_MAX_CONFIG; i++)
            {
                m_cbNumConfig.Items.Add(i);
            }

            m_cbNumConfig.TextChanged += new EventHandler(m_cbNumConfig_TextChanged);

            m_rbInternal.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbExternal.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbSingleEnded.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbDiff.CheckedChanged += new EventHandler(m_rb_CheckedChanged);

            m_chbSOC.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbLowPower.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnVrefVssa.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnModInput.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
        }
        #endregion

        #region Event handlers
        void m_cbNumConfig_TextChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            
            if (cb == m_cbNumConfig)
            {
                string errorMsg = string.Empty;
                byte value;

                if (byte.TryParse(cb.Text, out value))
                {
                    byte minValue = CyParamRanges.NUM_MIN_CONFIG;
                    byte maxValue = CyParamRanges.NUM_MAX_CONFIG;

                    // Reset parameters to default for unused configurations
                    for (byte i = (byte)(value + 1); i <= m_params.NumConfigurations; i++)
                    {
                        m_params.SetDefaultConfigParams(i);
                    }

                    m_params.NumConfigurations = value;

                    if (value >= minValue && value <= maxValue)
                    {
                        m_params.UpdateTabVisibility();
                    }
                    else
                    {
                        errorMsg = string.Format(Resource.NumConfigValueErrorDescription, minValue, maxValue);
                    }
                }
                else
                {
                    errorMsg = Resource.NumConfigFormatErrorDescription;
                }

                m_errorProvider.SetError(cb, errorMsg);
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chBox = sender as CheckBox;

            if (chBox != null)
            {
                if (chBox == m_chbSOC)
                {
                    m_params.UseTriggeredSamplingMode = chBox.Checked;
                }
                else if (chBox == m_chbLowPower)
                {
                    m_params.LowPowerChargePump = chBox.Checked;
                }
                else if (chBox == m_chbEnVrefVssa)
                {
                    m_params.EnableVrefVssa = chBox.Checked;
                }
                else if (chBox == m_chbEnModInput)
                {
                    m_params.EnableModulatorInput = chBox.Checked;
                }
            }
        }

        void m_rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;
            
            if (rb == m_rbInternal)
            {
                m_params.ClockSourceType = CyEClockSource.Internal;
                m_params.UpdateClockSourceDependencies();
            }
            else if (rb == m_rbExternal)
            {
                m_params.ClockSourceType = CyEClockSource.External;
                m_params.UpdateClockSourceDependencies();
            }

            else if (rb == m_rbSingleEnded)
            {
                m_params.InputModeType = CyEInputMode.Single_Mode;
                m_params.UpdateInputModeDependencies();
            }
            else if (rb == m_rbDiff)
            {
                m_params.InputModeType = CyEInputMode.Differential_Mode;
                m_params.UpdateInputModeDependencies();
            }
        }
        #endregion
    }
}
