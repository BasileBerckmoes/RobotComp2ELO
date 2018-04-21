/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;

namespace DMA_Channel_P4_v1_0.Tabs
{
    public partial class CyGeneralTab : CyTabControlWrapper
    {

        #region Class Properties
        public override string TabName
        {
            get { return "Channel"; }
        }
        #endregion

        #region Constructor
        public CyGeneralTab(CyParameters param)
            : base(param)
        {
            m_params.m_generalTab = this;
            
            InitializeComponent();

            string[] s1 = new string[] { "0 (Highest)", "1", "2", "3 (Lowest)" };
            string[] s2 = new string[] { "1", "2" };

            m_cmbChannelPriority.Items.AddRange(s1);
            m_cmbNumberOfDescriptors.Items.AddRange(s2);

            #region Add event handlers

            m_chbEnableTrIn.CheckedChanged += chb_CheckedChanged;

            m_cmbNumberOfDescriptors.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbChannelPriority.SelectedIndexChanged += cmb_SelectedIndexChanged;
            #endregion    
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            m_chbEnableTrIn.Checked = m_params.EnableTrIn;

            if (m_cmbNumberOfDescriptors.Items.Count >= m_params.TdNum && m_params.TdNum != 0)
            {
                m_cmbNumberOfDescriptors.SelectedIndex = (byte)(m_params.TdNum - 1); 
            }
            if (m_cmbChannelPriority.Items.Count > m_params.ChanPriority)
            {
                m_cmbChannelPriority.SelectedIndex = (byte)m_params.ChanPriority; 
            }
        }
        #endregion

        #region Event Handlers
        private void cmb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cmb = (ComboBox)sender;

            if (cmb == m_cmbChannelPriority)
                m_params.ChanPriority = (byte)cmb.SelectedIndex;
            else if (cmb == m_cmbNumberOfDescriptors)
            {
                m_params.TdNum = (byte)(cmb.SelectedIndex + 1);
                m_params.UpdateTabVisibility();
            }
        }

        private void chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = (CheckBox)sender;

            if (chb == m_chbEnableTrIn)
                m_params.EnableTrIn = chb.Checked;
        }
        #endregion
    }
}