/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;

namespace SCB_P4_v4_0
{
    public partial class CyUARTPinsTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return "UART Pins";
            }
        }

        public override string TabDisplayName
        {
            get { return Resources.UARTPinsTabDisplayName; }
        }

        #endregion

        public CyUARTPinsTab(CyParameters parameters, ICyTabbedParamEditor editor)
            : base(parameters, editor)
        {
            InitializeComponent();

            m_params.ScbModeChanged += m_params_ScbModeChanged;

            m_params.UartWakeupChanged += delegate
            {
                ValidateShowTerminals();
            };
        }

        #region Assigning parameters values to controls

        public override void UpdateUI()
        {
            m_chbShowTerminals.Checked = m_params.UART_SmartioEnable;
            ValidateShowTerminals();
        }

        #endregion
        
        #region Validation

        private void ValidateShowTerminals()
        {
            if (m_params.UART_SmartioEnable && m_params.UART_WakeupFromSleepEnabled)
            {
                m_errorProvider.SetError(m_chbShowTerminals, Resources.ShowTerminalsWakeUpError);
            }
            else
            {
                m_errorProvider.SetError(m_chbShowTerminals, string.Empty);
            }
        }

        #endregion

        #region Event handlers

        void m_params_ScbModeChanged(object sender, CyScbModeChangedEventArgs e)
        {
            if (e.Mode == CyESCBMode.UART)
                ShowTab();
            else
                HideTab();
        }

        private void m_chbShowTerminals_CheckedChanged(object sender, EventArgs e)
        {
            m_params.UART_SmartioEnable = m_chbShowTerminals.Checked;
            ValidateShowTerminals();
            m_params.OnUartShowTerminalsChanged(sender, e);
        }
        #endregion
    }
}
