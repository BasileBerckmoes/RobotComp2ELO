/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using DMA_PDL_v2_0.Utils;

namespace DMA_PDL_v2_0.Tabs
{
    internal partial class CyBasicTab : CyTabBase, ICyTab
    {
        public CyBasicTab(CyParameters parameters) :
            base(parameters)
        {
            InitializeComponent();
            this.m_numberOfDescriptorsNumericUpDown.UserMaximum = CyConst.R_NUMBER_OF_DESCRIPTORS_DEF.Max;
            this.m_numberOfDescriptorsNumericUpDown.UserMinimum = CyConst.R_NUMBER_OF_DESCRIPTORS_DEF.Min;

            m_triggerInputComboBox.DataSource = Enum.GetValues(typeof(CyEnDisEnum));
            m_triggerOutputComboBox.DataSource = Enum.GetValues(typeof(CyEnDisEnum));
            m_preemptableComboBox.DataSource = Enum.GetValues(typeof(CyEnDisEnum));
        }

        public string TabName
        {
            get
            {
                return CyCustomizer.BASIC_TAB_NAME;
            }
        }

        public void UpdateUI()
        {
            m_numberOfDescriptorsNumericUpDown.Text = m_parameters.NumberOfDescriptors.ToString();
            m_triggerInputComboBox.SelectedItem = m_parameters.TriggerInput ? CyEnDisEnum.Enable : CyEnDisEnum.Disable;
            m_triggerOutputComboBox.SelectedItem = m_parameters.TriggerOutput ? CyEnDisEnum.Enable : CyEnDisEnum.Disable;
            m_channelPriorityComboBox.SelectedIndex = m_parameters.ChannelPriority;
            m_preemptableComboBox.SelectedItem = m_parameters.Preemptable ? CyEnDisEnum.Enable : CyEnDisEnum.Disable;
        }

        #region Event handlers

        private void m_triggerInputComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.TriggerInput = Convert.ToBoolean(m_triggerInputComboBox.SelectedIndex);
        }

        private void m_triggerOutputComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.TriggerOutput = Convert.ToBoolean(m_triggerOutputComboBox.SelectedIndex);
        }

        private void m_channelPriorityComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.ChannelPriority = m_channelPriorityComboBox.SelectedIndex;
        }

        private void m_preemptableComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.Preemptable = Convert.ToBoolean(m_preemptableComboBox.SelectedIndex);
        }

        private void m_numberOfDescriptorsNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_parameters.NumberOfDescriptors = Convert.ToByte(m_numberOfDescriptorsNumericUpDown.Value);
        }
        #endregion

    }
}
