/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;

namespace SMBusSlave_v5_20
{
    public partial class CyI2cConfigP4Tab : CyTabWrapper
    {
        #region CyTabWrapper members
        public override string TabName
        {
            get
            {
                return "I2C Configuration P4";
            }
        }
        #endregion

        #region Constructor(s)
        public CyI2cConfigP4Tab(CyParameters parameters)
            : base(parameters)
        {            
            InitializeComponent();
            m_params.I2cConfigP4Tab = this;
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            chbClockFromTerminal.Checked = m_params.ClockFromTerm;
        }
        #endregion Update UI

        #region Event handlers
        private void chbClockFromTerminal_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                m_params.ClockFromTerm = chbClockFromTerminal.Checked;
                m_params.GeneralTab.UpdateClockDependencies();
                m_params.UpdateTimeout();
            }
        }
        #endregion Event handlers
    }
}
