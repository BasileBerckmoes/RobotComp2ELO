/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace ScanComp_v1_10
{
    public partial class CyChannelsTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return "Channels"; }
        }

        private UInt16 m_defaultVDACVoltage;
        private List<UInt16> m_perChannelDacVoltageCopy = new List<UInt16>();

        #region Constructor(s)
        public CyChannelsTab(CyParameters parameters)
            : base(parameters)
        {
            m_params = parameters;
            m_params.ChannelsTab = this;
            InitializeComponent();

            numChannels.Minimum = 0;
            numChannels.Maximum = Decimal.MaxValue;

            // Fill in combobox cells in DataGridView
            colInterruptMode.Items.Clear();
            colInterruptMode.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEChannelIntMode)));

            dgvChannels.Tag = CyEDataDrid.Channels;
            CyParameters.SetReadOnlyState(colChannelNum, true);
            dgvChannels.CurrentCellDirtyStateChanged += delegate(object sender, EventArgs e)
            {
                CommitCellValueImmediately(sender as DataGridView);
            };

            #region SubscribeEvents
            numChannels.TextChanged += numChannels_TextChanged;
            #endregion
        }
        #endregion

        #region Overrides
        /// <summary>
        /// Prevents resetting UserControl scroll bar
        /// </summary>
        protected override Point ScrollToControl(Control activeControl)
        {
            return DisplayRectangle.Location;
        }
        #endregion

        #region Update tab controls from parameters
        /// <summary>
        /// Update tab controls with values from parameters
        /// </summary>
        public void UpdateUI()
        {
            numChannels.Value = m_params.SequencedChannels;
            UpdateUIFromTable();
        }
        #endregion

        #region Update data grid from array
        /// <summary>
        /// Update Channels DataGridView with values from table
        /// </summary>
        public void UpdateUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            dgvChannels.Rows.Clear();

            // Add all sequenced channels
            int numChannels = m_params.SequencedChannels;
            for (int dgvRowIndex = 0; dgvRowIndex < numChannels; dgvRowIndex++)
            {
                dgvChannels.Rows.Add(new object[dgvChannels.ColumnCount]);
                UpdateUIFromTable(dgvRowIndex);
            }

            ValidateColumn(colDacVoltage);

            // Correct DataGridView height
            dgvChannels.Height = dgvChannels.ColumnHeadersHeight + numChannels * dgvChannels.RowTemplate.Height + 2;

            m_params.GlobalEditMode = prevGEM;
        }

        /// <summary>
        /// Update specific row in Channels DataGridView with data from table
        /// </summary>
        /// <param name="rowIndex"></param>
        public void UpdateUIFromTable(int rowIndex)
        {
            dgvChannels[colChannelNum.Index, rowIndex].Value = rowIndex.ToString();
            dgvChannels[colInterruptMode.Index, rowIndex].Value =
                CyEnumConverter.GetEnumDesc(m_params.ChannelsTable[rowIndex].InterruptMode);
            dgvChannels[colDacVoltage.Index, rowIndex].Value = m_params.ChannelsTable[rowIndex].DacVoltage;
        }
        #endregion

        #region Update table from data grid
        /// <summary>
        /// Update table with data from specific row in DataGridView
        /// </summary>
        /// <param name="rowIndex"></param>
        public void UpdateTableRowFromUI(int rowIndex)
        {
            if (rowIndex >= 0 && rowIndex < dgvChannels.RowCount)
            {
                m_params.ChannelsTable[rowIndex].InterruptMode = CyEnumConverter.GetEnumValue<CyEChannelIntMode>(
                    dgvChannels[colInterruptMode.Index, rowIndex].Value);
                m_params.ChannelsTable[rowIndex].DacVoltage =
                    CyParameters.ConvertToUInt16(dgvChannels[colDacVoltage.Index, rowIndex].Value);
            }
        }
        #endregion

        #region Event Handlers
        private void dgvChannels_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                ValidateDataGridCellRange(e.ColumnIndex, e.RowIndex);
                UpdateTableRowFromUI(e.RowIndex);  // update table with data from DatagridView
                m_params.SetChannelsConfigTable(); // set current data to the component
            }
        }

        private void numChannels_TextChanged(object sender, EventArgs e)
        {
            string errorMsg = String.Empty;
            byte value;
            bool parsed = Byte.TryParse(numChannels.Text, out value);

            if (parsed && m_params.GlobalEditMode)
            {
                m_params.SequencedChannels = value;
            }

            if (parsed && value >= CyParamRanges.NUM_CHANNELS_MIN && value <= CyParamRanges.NUM_CHANNELS_MAX)
            {
                // Add new channels
                int currentChannelsCount = m_params.ChannelsTable.Count;
                if (currentChannelsCount < value)
                {
                    int rowsToAddCount = value - currentChannelsCount;
                    for (int i = 0; i < rowsToAddCount; i++)
                    {
                        m_params.ChannelsTable.Add(CyChannelsTableRow.CreateDefaultRow());
                        m_params.ChannelsTable[m_params.ChannelsTable.Count - 1].DacVoltage = m_defaultVDACVoltage;
                    }
                }

                UpdateUIFromTable();
            }
            else // if number of channels is not valid
            {
                errorMsg = String.Format(Resources.NumSeqChannelsFormatErrorDescription,
                    CyParamRanges.NUM_CHANNELS_MIN, CyParamRanges.NUM_CHANNELS_MAX);
            }

            if (string.IsNullOrEmpty(errorMsg))
            {
                m_params.SetChannelsConfigTable(); // save changes if number of channels is valid
            }
            m_errorProvider.SetError(numChannels, errorMsg);
        }

        private void CyChannelsTab_VisibleChanged(object sender, EventArgs e)
        {
            // Set column readonly before the validation. Validation will ignore errors for disabled cells
            CyParameters.SetReadOnlyState(colDacVoltage, (m_params.NegativeInput != CyENegativeInput.INTERN ||
                m_params.VdacVoltageMode == CyEVdacVoltageMode.FIXED));
            ValidateColumn(colDacVoltage);
        }

        public void UpdateDacVoltageColumn()
        {
            if (m_params.VdacVoltageMode == CyEVdacVoltageMode.FIXED)
            {
                bool needCopy = (m_perChannelDacVoltageCopy.Count == 0);
                bool needReplaceWithFixedVoltage = (m_defaultVDACVoltage != m_params.VdacVoltageMv) || needCopy;

                if (needCopy)
                {
                    // VDAC voltage mode switched to Fixed
                    for (int rowIndex = 0; rowIndex < m_params.ChannelsTable.Count; rowIndex++)
                    {
                        m_perChannelDacVoltageCopy.Add(m_params.ChannelsTable[rowIndex].DacVoltage);
                    }
                }

                if (needReplaceWithFixedVoltage)
                {
                    // VDAC voltage mode switched to Fixed or Fixed Voltage was changed
                    UInt16 fixedVoltage = m_params.VdacVoltageMv;
                    for (int rowIndex = 0; rowIndex < m_params.ChannelsTable.Count; rowIndex++)
                    {
                        m_params.ChannelsTable[rowIndex].DacVoltage = fixedVoltage;
                    }
                    m_defaultVDACVoltage = fixedVoltage;
                    m_params.SetChannelsConfigTable();
                    UpdateUIFromTable();
                }
            }
            else
            {
                if (m_perChannelDacVoltageCopy.Count > 0) // VDAC voltage mode switched to Per channel
                {
                    for (int rowIndex = 0; rowIndex < m_perChannelDacVoltageCopy.Count; rowIndex++)
                    {
                        m_params.ChannelsTable[rowIndex].DacVoltage = m_perChannelDacVoltageCopy[rowIndex];
                    }
                    m_perChannelDacVoltageCopy.Clear();
                    m_params.SetChannelsConfigTable();
                    UpdateUIFromTable();
                }
                m_defaultVDACVoltage = m_params.GetDefaultDACVoltage();
            }
        }
        #endregion

        #region Data grid validation
        private void ValidateColumn(DataGridViewTextBoxColumn column)
        {
            for (int i = 0; i < dgvChannels.RowCount; i++)
            {
                ValidateDataGridCellRange(column.Index, i);
            }
        }

        private bool ValidateDataGridCellRange(int colIndex, int rowIndex)
        {
            DataGridViewCell dgvCell = dgvChannels[colIndex, rowIndex];
            UInt16 currCellValue = 0;
            string errorMessage = String.Empty;
            int min;
            int max;

            if (dgvCell.ReadOnly) // read-only cells may contain any value
            {
                dgvCell.ErrorText = String.Empty;
                return true;
            }

            if (colIndex == colDacVoltage.Index)
            {
                min = CyParamRanges.VDAC_VOLTAGE_MIN;
                max = m_params.GetMaxDACVoltage();
            }
            else
            {
                return true; // the column should not be validated
            }

            if (dgvCell.Value != null && UInt16.TryParse(dgvCell.Value.ToString(), out currCellValue))
            {
                if (currCellValue < min || currCellValue > max)
                    errorMessage = string.Format(Resources.ValueOutOfRange, min, max);
            }
            else
            {
                errorMessage = string.Format(Resources.ValueOutOfRange, min, max);
            }

            dgvCell.ErrorText = errorMessage;

            return String.IsNullOrEmpty(errorMessage);
        }
        #endregion

        /// <summary>
        /// Commits value selected in ComboBox or CheckBox control which belongs DataGridView control
        /// </summary>
        protected void CommitCellValueImmediately(DataGridView dataGridView)
        {
            if (dataGridView.CurrentCell != null)
                if (dataGridView.CurrentCell.GetType() == typeof(DataGridViewComboBoxCell) ||
                    dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell))
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
        }
    }
}
 
