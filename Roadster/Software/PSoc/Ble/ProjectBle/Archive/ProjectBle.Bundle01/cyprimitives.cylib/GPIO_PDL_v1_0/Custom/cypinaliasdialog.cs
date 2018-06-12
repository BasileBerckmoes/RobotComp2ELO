/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    [ExcludeFromCodeCoverage]
    public partial class CyPinAliasDialog : Form
    {
        int m_pinNum;

        internal CyPinAliasDialog(string pinName, string alias, int pinNum)
        {
            InitializeComponent();

            m_pinNum = pinNum;
            Text = string.Format(Resource1.Prompt_ChangeAlias, pinName);

            m_aliasTextBox.Text = alias;
            m_errorProvider.SetIconAlignment(m_aliasTextBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_aliasTextBox, 3);
            UpdateError();

            m_aliasTextBox.TextChanged += m_aliasTextBox_TextChanged;
            m_aliasTextBox.Validating += m_aliasTextBox_Validating;
        }

        void m_aliasTextBox_Validating(object sender, CancelEventArgs e)
        {
            string errMsg = m_errorProvider.GetError(m_aliasTextBox);
            e.Cancel = !string.IsNullOrEmpty(errMsg);
        }

        void m_aliasTextBox_TextChanged(object sender, EventArgs e)
        {
            UpdateError();
        }

        void UpdateError()
        {
            CyCustErr err = CyPinData.ValidateAlias(m_pinNum, m_aliasTextBox.Text);
            m_errorProvider.SetError(m_aliasTextBox, err.IsNotOk ? err.Message : string.Empty);
            m_okButton.Enabled = !err.IsNotOk;
        }

        internal string Alias
        {
            get { return m_aliasTextBox.Text; }
        }
    }
}
