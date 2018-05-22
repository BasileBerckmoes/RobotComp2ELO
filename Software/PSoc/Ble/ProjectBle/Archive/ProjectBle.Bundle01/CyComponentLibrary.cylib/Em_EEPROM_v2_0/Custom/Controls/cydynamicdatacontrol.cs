/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace Em_EEPROM_v2_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        private readonly CyParameters m_params;

        #region Constructor(s)
        public CyDynamicDataControl(CyParameters parameters)
        {
            InitializeComponent();
            Dock = DockStyle.Fill;
            AutoScroll = true;

            m_params = parameters;
        }
        #endregion

        #region UI update
        public void UpdateUI(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            m_lblActualSizeValue.Text = m_params.ActualSize.ToString();
        }
        #endregion
    }
}
