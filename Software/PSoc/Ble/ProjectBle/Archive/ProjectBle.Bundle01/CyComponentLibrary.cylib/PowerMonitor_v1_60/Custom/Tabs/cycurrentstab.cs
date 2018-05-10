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
using CyDesigner.Extensions.Gde;

namespace PowerMonitor_v1_60
{
    public partial class CyCurrentsTab : CyEditingWrapperControl
    {
        private int m_dataGridRowCount;
        private List<int> m_sanityCheckCols;
        private List<int> m_rangeCheckCols;

        #region Class properties
        public override string TabName
        {
            get { return "Power Converter Currents"; }
        }

        public int DataGridRowCount
        {
            get { return m_dataGridRowCount; }
            set
            {
                m_dataGridRowCount = value;
                dataGridView1.RowCount = m_dataGridRowCount;
            }
        }

        public int DataGridFirstSelectedRow
        {
            get { return GetLessSelectedRow(dataGridView1.SelectedRows); }
        }
        #endregion

        #region Constructor(s)
        public CyCurrentsTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params.m_currentsTab = this;

            InitializeComponent();

            // Initialize toolstrip
            cyToolStrip1.SetParameters(param);
            cyToolStrip1.m_dgv = dataGridView1;

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip1;
            m_wrapperDataGridView = dataGridView1;
            m_currentsTableErrors = new List<string[]>();
            for (int i = 0; i < CyParamRanges.NUM_CONVERTERS_MAX; i++)
                m_currentsTableErrors.Add(new string[dataGridView1.ColumnCount]);

            // Initialize data grid view
            dataGridView1.EditMode = DataGridViewEditMode.EditOnEnter;
            this.colCurrentMeasurementType.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(
                CyECurrentMeasurementInternalType)));
            dataGridView1.AllowUserToOrderColumns = false;
            dataGridView1.AllowUserToResizeRows = false;
            dataGridView1.AllowUserToAddRows = false;
            foreach (DataGridViewColumn item in dataGridView1.Columns)
                item.SortMode = DataGridViewColumnSortMode.Programmatic;

            m_sanityCheckCols = new List<int>();
            m_sanityCheckCols.Add(colOcWarningThreshold.Index);
            m_sanityCheckCols.Add(colOcFaultThreshold.Index);
            m_sanityCheckCols.Add(colCurrentMeasurementType.Index);

            m_rangeCheckCols = new List<int>();
            m_rangeCheckCols.Add(colCurrentMeasurementType.Index);
            m_rangeCheckCols.Add(colOcWarningThreshold.Index);
            m_rangeCheckCols.Add(colOcFaultThreshold.Index);
            m_rangeCheckCols.Add(colShuntResistorValue.Index);
            m_rangeCheckCols.Add(colCsaGain.Index);

            // Fill data grid view
            UpdateUIFromTable();
            ValidateAllCells();
            UpdateColumnsVisibility();
        }
        #endregion

        #region Event Handlers
        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                UpdateTableFromUI();
                m_params.SetCurrentsTable();

                ValidateRow(e);

                if (e.ColumnIndex == colCurrentMeasurementType.Index)
                {
                    m_params.m_voltagesTab.ValidateRow(e.RowIndex);
                }
            }
        }

        public void ValidateRow(int rowIndex)
        {
            ValidateRow(new DataGridViewCellEventArgs(colCurrentMeasurementType.Index, rowIndex));
        }

        private void ValidateRow(DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != colConverterName.Index &&
                e.ColumnIndex != colNominalOutputVoltage.Index) // do not check when readonly cells changed
            {
                string errorMessage = string.Empty;

                UpdateRowVisibility(e.RowIndex);

                // Range check
                bool rangeIsValid = true;
                for (int i = 0; i < m_rangeCheckCols.Count; i++)
                {
                    errorMessage = RangeCheck(e.RowIndex, m_rangeCheckCols[i]);
                    if (errorMessage != string.Empty)
                        rangeIsValid = false;
                    m_currentsTableErrors[e.RowIndex].SetValue(errorMessage, m_rangeCheckCols[i]);
                }
                if (rangeIsValid)
                {
                    // Range is OK. Do sanity check
                    for (int i = 0; i < m_sanityCheckCols.Count; i++)
                    {
                        errorMessage = SanityCheck(e.RowIndex, m_sanityCheckCols[i]);
                        m_currentsTableErrors[e.RowIndex].SetValue(errorMessage, m_sanityCheckCols[i]);
                    }
                }
            }
        }

        private void dataGridView1_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(dataGridView1);
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            cyToolStrip1.ChangeCopyPasteEnabling(dataGridView1.SelectedRows.Count > 0);
        }
        #endregion

        #region Communication between object and UI

        public void UpdateUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            m_dataGridRowCount = m_params.NumConverters;
            dataGridView1.Rows.Clear();

            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                object[] row = new object[] { 
                    CyCurrentsTableRow.GetPowerConverterNumber(i), 
                    m_params.VoltagesTable[i].m_converterName, 
                    m_params.VoltagesTable[i].m_nominalOutputVoltage, 
                    CyEnumConverter.GetEnumDesc(m_params.CurrentsTable[i].m_currentMeasurementType), 
                    m_params.CurrentsTable[i].m_ocWarningThreshold,
                    m_params.CurrentsTable[i].m_ocFaulthTreshold,
                    m_params.CurrentsTable[i].m_shuntResistorValue,
                    m_params.CurrentsTable[i].m_csaGain,
                };

                dataGridView1.Rows.Add(row);

                UpdateRowVisibility(i);
            }
            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateTableFromUI()
        {
            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                m_params.CurrentsTable[i].m_currentMeasurementType = (CyECurrentMeasurementInternalType)
                    CyEnumConverter.GetEnumValue(dataGridView1.Rows[i].Cells[colCurrentMeasurementType.Index].Value,
                    typeof(CyECurrentMeasurementInternalType));

                if (dataGridView1.Rows[i].Cells[colOcWarningThreshold.Index].ReadOnly == false)
                {
                    m_params.CurrentsTable[i].m_ocWarningThreshold = CyParameters.ParseNullableDouble(
                        dataGridView1.Rows[i].Cells[colOcWarningThreshold.Index].Value);
                }

                if (dataGridView1.Rows[i].Cells[colOcFaultThreshold.Index].ReadOnly == false)
                {
                    m_params.CurrentsTable[i].m_ocFaulthTreshold = CyParameters.ParseNullableDouble(
                        dataGridView1.Rows[i].Cells[colOcFaultThreshold.Index].Value);
                }

                if (dataGridView1.Rows[i].Cells[colShuntResistorValue.Index].ReadOnly == false)
                {
                    m_params.CurrentsTable[i].m_shuntResistorValue = CyParameters.ParseNullableDouble(
                        dataGridView1.Rows[i].Cells[colShuntResistorValue.Index].Value);
                }

                if (dataGridView1.Rows[i].Cells[colCsaGain.Index].ReadOnly == false)
                {
                    m_params.CurrentsTable[i].m_csaGain = CyParameters.ParseNullableDouble(
                        dataGridView1.Rows[i].Cells[colCsaGain.Index].Value);
                }
            }
        }

        void UpdateRowVisibility(int row)
        {
            bool readOnly = false;
            //Any converter that was set to VType = Differential in the voltages tab forfeits 
            //the capability to measure current. The associated row in this table will be grayed out and
            //current measurement type column entry will set to "None"
            CyParameters.SetCellReadOnlyState(dataGridView1, row, colCurrentMeasurementType.Index,
                m_params.VoltagesTable[row].m_voltageMeasurementType == CyEVInternalType.Differential);

            //CSAGainp is grayed out if the associated IType[x] is set to None or Direct.
            CyParameters.SetCellReadOnlyState(dataGridView1, row, colCsaGain.Index,
                m_params.CurrentsTable[row].m_currentMeasurementType != CyECurrentMeasurementInternalType.CSA);

            //This entry is grayed out if the associated IType[x] is set to None ot WarningSourcesOC is false. 
            readOnly = !m_params.WarningSourcesOC ||
                m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None;
            CyParameters.SetCellReadOnlyState(dataGridView1, row, colOcWarningThreshold.Index, readOnly);

            //This entry is grayed out if the associated IType[x] is set to None or FaultSourcesOC is false. 
            readOnly = !m_params.FaultSourcesOC ||
                m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None;
            CyParameters.SetCellReadOnlyState(dataGridView1, row, colOcFaultThreshold.Index, readOnly);

            //This entry is grayed out if the associated IType[x] is set to None. 
            CyParameters.SetCellReadOnlyState(dataGridView1, row, colShuntResistorValue.Index,
                m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None);

            UpdateRowValues(row);
        }

        /// <summary>
        /// This method updates cells in columns "OC warning threshold", "OC fault threshold", "Shunt resistor value"
        /// and "CSA gain". If the cell is readonly, it sets cell allignment to MiddleCenter and sets value to "-".
        /// Otherwise, it sets cell allignment to MiddleLeft and displays property's current value in the cell.
        /// </summary>
        /// <param name="row">Row index</param>
        private void UpdateRowValues(int row)
        {
            DataGridViewCellStyle cellStyle = new DataGridViewCellStyle();

            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            if (m_params.WarningSourcesOC == false ||
                m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None)
            {
                dataGridView1[colOcWarningThreshold.Index, row].Value = "-";
                dataGridView1[colOcWarningThreshold.Index, row].Style = CyParameters.DGDisabledCenteredStyle;
            }
            else
            {
                dataGridView1[colOcWarningThreshold.Index, row].Value =
                    m_params.CurrentsTable[row].m_ocWarningThreshold;
                dataGridView1[colOcWarningThreshold.Index, row].Style = CyParameters.DGEnabledStyle;
            }

            if (m_params.FaultSourcesOC == false ||
                m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None)
            {
                dataGridView1[colOcFaultThreshold.Index, row].Value = "-";
                dataGridView1[colOcFaultThreshold.Index, row].Style = CyParameters.DGDisabledCenteredStyle;
            }
            else
            {
                dataGridView1[colOcFaultThreshold.Index, row].Value =
                    m_params.CurrentsTable[row].m_ocFaulthTreshold;
                dataGridView1[colOcFaultThreshold.Index, row].Style = CyParameters.DGEnabledStyle;
            }

            if (m_params.CurrentsTable[row].m_currentMeasurementType == CyECurrentMeasurementInternalType.None)
            {
                dataGridView1[colShuntResistorValue.Index, row].Value = "-";
                dataGridView1[colShuntResistorValue.Index, row].Style = CyParameters.DGDisabledCenteredStyle;
            }
            else
            {
                dataGridView1[colShuntResistorValue.Index, row].Value =
                    m_params.CurrentsTable[row].m_shuntResistorValue;
                dataGridView1[colShuntResistorValue.Index, row].Style = CyParameters.DGEnabledStyle;
            }

            if (m_params.CurrentsTable[row].m_currentMeasurementType != CyECurrentMeasurementInternalType.CSA)
            {
                dataGridView1[colCsaGain.Index, row].Value = "-";
                dataGridView1[colCsaGain.Index, row].Style = CyParameters.DGDisabledCenteredStyle;
            }
            else
            {
                dataGridView1[colCsaGain.Index, row].Value =
                    m_params.CurrentsTable[row].m_csaGain;
                dataGridView1[colCsaGain.Index, row].Style = CyParameters.DGEnabledStyle;
            }
            m_params.GlobalEditMode = prevGEM;
        }

        public void SelectDataGridViewRows(int fromRow, int toRow)
        {
            SelectRows(dataGridView1, fromRow, toRow);
        }

        public void UpdateColumnsState()
        {
            for (int i = 0; i < dataGridView1.RowCount; i++)
                UpdateRowVisibility(i);
        }

        public void UpdateColumnsVisibility()
        {
            colOcFaultThreshold.Visible = m_params.FaultSourcesOC;
            colOcWarningThreshold.Visible = m_params.WarningSourcesOC;
        }
        #endregion

        #region Validation
        private string RangeCheck(int rowIndex, int colIndex)
        {
            string columnName = dataGridView1.Columns[colIndex].Name;
            double min;
            double max;
            string message = string.Empty;

            if (columnName == colOcWarningThreshold.Name && m_params.WarningSourcesOC)
            {
                min = CyParamRanges.OC_WARNING_TRESHOLD_MIN;
                max = CyParamRanges.OC_WARNING_TRESHOLD_MAX;
                message = Resources.OcWarningThresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colOcFaultThreshold.Name && m_params.FaultSourcesOC)
            {
                min = CyParamRanges.OC_FAULT_TRESHOLD_MIN;
                max = CyParamRanges.OC_FAULT_TRESHOLD_MAX;
                message = Resources.OcFaultThresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colShuntResistorValue.Name)
            {
                min = CyParamRanges.SHUNT_RESISTOR_MIN;
                max = CyParamRanges.SHUNT_RESISTOR_MAX;
                message = Resources.ShuntResistorError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colCsaGain.Name)
            {
                min = CyParamRanges.CSA_GAIN_MIN;
                max = CyParamRanges.CSA_GAIN_MAX;
                message = Resources.CsaGainError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                  string.Empty : string.Format(message, min, max);
            }

            return message;
        }

        private string SanityCheck(int rowIndex, int colIndex)
        {
            string message = string.Empty;
            double? ocWarningThreshold = 0;
            double? ocFaultThreshold = 0;
            double? shunt = 0;
            double? csagain = 0;

            try
            {
                ocWarningThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colOcWarningThreshold.Index].Value);
                ocFaultThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colOcFaultThreshold.Index].Value);
                shunt = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colShuntResistorValue.Index].Value);

                if (m_params.CurrentsTable[rowIndex].m_currentMeasurementType == CyECurrentMeasurementInternalType.CSA)
                {
                    csagain = CyParameters.ParseNullableDouble(
                        dataGridView1.Rows[rowIndex].Cells[colCsaGain.Index].Value);
                }

                if (dataGridView1.Columns[colIndex].Name == colCurrentMeasurementType.Name)
                {
                    if (m_params.CurrentsTable[rowIndex].m_currentMeasurementType ==
                        CyECurrentMeasurementInternalType.Direct &&
                        m_params.VoltagesTable[rowIndex].m_inputScalingFactor != CyParamRanges.DIRECT_MODE_LIMIT)
                    {
                        message = Resources.InputScalingFactorNotEqualOne;
                        dataGridView1.Rows[rowIndex].Cells[colCurrentMeasurementType.Index].ErrorText = message;
                    }
                    else
                    {
                        message = string.Empty;
                        dataGridView1.Rows[rowIndex].Cells[colCurrentMeasurementType.Index].ErrorText = message;
                    }
                }

                // Do nothing if Measurement Type is None
                if (m_params.CurrentsTable[rowIndex].m_currentMeasurementType ==
                    CyECurrentMeasurementInternalType.None)
                {
                    return message;
                }

                if (dataGridView1.Columns[colIndex].Name == colOcWarningThreshold.Name && m_params.WarningSourcesOC)
                {
                    if (ocWarningThreshold != null)
                    {
                        //OCWarn[x] <= OCFault[x]
                        if (ocWarningThreshold > ocFaultThreshold && m_params.FaultSourcesOC)
                        {
                            message = Resources.OcWarningThresholdSanityCheck;
                            dataGridView1.Rows[rowIndex].Cells[colOcWarningThreshold.Index].ErrorText = message;
                        }
                        else
                        {
                            message = string.Empty;
                            dataGridView1.Rows[rowIndex].Cells[colOcWarningThreshold.Index].ErrorText = message;
                        }
                    }
                }
                else if (dataGridView1.Columns[colIndex].Name == colOcFaultThreshold.Name && m_params.FaultSourcesOC)
                {
                    if (ocFaultThreshold != null)
                    {
                        message = string.Empty;
                        if (m_params.CurrentsTable[rowIndex].m_currentMeasurementType ==
                            CyECurrentMeasurementInternalType.Direct)
                        {
                            if ((ocFaultThreshold * shunt) > m_params.GetCurrentRange())
                                message = string.Format(Resources.OcFaultThresholdSanityCheck, m_params.GetCurrentRange());
                        }
                        else if (m_params.CurrentsTable[rowIndex].m_currentMeasurementType ==
                            CyECurrentMeasurementInternalType.CSA)
                        {
                            double max = (m_params.LowVoltageMode == CyELowVoltageMode.Range_2048mV) ?
                                CyParamRanges.ADC_RANGE_CSA_CHECK_2V : CyParamRanges.ADC_RANGE_CSA_CHECK_4V;
                            if ((ocFaultThreshold * shunt * csagain) > max)
                                message = string.Format(Resources.OcFaultThresholdCSASanityCheck, max / 1000.0);
                        }

                        dataGridView1.Rows[rowIndex].Cells[colOcFaultThreshold.Index].ErrorText = message;
                    }
                }
            }
            catch (Exception)
            {
                System.Diagnostics.Debug.Assert(false);
            }
            return message;
        }

        public void ValidateAllCells()
        {
            bool prev_edit_mode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                for (int j = 0; j < dataGridView1.Rows[i].Cells.Count; j++)
                {
                    ValidateRow(new DataGridViewCellEventArgs(j, i));
                }
            }
            m_params.GlobalEditMode = prev_edit_mode;
        }
        #endregion
    }
}
