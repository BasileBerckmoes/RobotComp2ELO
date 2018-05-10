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

namespace PowerMonitor_P4_v2_10
{
    public partial class CyVoltagesTab : CyEditingWrapperControl
    {
        private int m_dataGridRowCount;
        private List<int> m_sanityCheckCols;
        private List<int> m_rangeCheckCols;

        #region Class properties
        public override string TabName
        {
            get { return "Power Converter Voltages"; }
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
        public CyVoltagesTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params.m_voltagesTab = this;

            InitializeComponent();

            // Initialize toolstrip
            cyToolStrip1.SetParameters(param);
            cyToolStrip1.m_dgv = dataGridView1;

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip1;
            m_wrapperDataGridView = dataGridView1;
            m_voltagesTableErrors = new List<string[]>();
            for (int i = 0; i < CyParamRanges.NUM_CONVERTERS_MAX; i++)
                m_voltagesTableErrors.Add(new string[dataGridView1.ColumnCount]);

            // Initialize data grid view
            dataGridView1.EditMode = DataGridViewEditMode.EditOnEnter;
            //byg this.colVoltageMeasurementType.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEVInternalType)));
            dataGridView1.AllowUserToOrderColumns = false;
            dataGridView1.AllowUserToResizeRows = false;
            dataGridView1.AllowUserToAddRows = false;
            foreach (DataGridViewColumn item in dataGridView1.Columns)
                item.SortMode = DataGridViewColumnSortMode.Programmatic;

            // Arrays for validating parameters
            m_sanityCheckCols = new List<int>();
            //byg_todo m_sanityCheckCols.Add(colAcqTime.Index);
            m_sanityCheckCols.Add(colUVFaultThreshold.Index);
            m_sanityCheckCols.Add(colUVWarningThreshold.Index);
            m_sanityCheckCols.Add(colOVWarningThreshold.Index);
            m_sanityCheckCols.Add(colOVFaultThreshold.Index);
            m_sanityCheckCols.Add(colInputScalingFactor.Index);

            m_rangeCheckCols = new List<int>();
            m_rangeCheckCols.Add(colNominalOutputVoltage.Index);
            m_rangeCheckCols.Add(colAcqTime.Index);
            m_rangeCheckCols.Add(colUVFaultThreshold.Index);
            m_rangeCheckCols.Add(colUVWarningThreshold.Index);
            m_rangeCheckCols.Add(colOVWarningThreshold.Index);
            m_rangeCheckCols.Add(colOVFaultThreshold.Index);
            m_rangeCheckCols.Add(colInputScalingFactor.Index);

            CyParameters.DGDisabledStyle = new DataGridViewCellStyle(dataGridView1.Columns[0].DefaultCellStyle);
            CyParameters.DGDisabledCenteredStyle = new DataGridViewCellStyle(dataGridView1.Columns[0].DefaultCellStyle);
            CyParameters.DGDisabledCenteredStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            CyParameters.DGEnabledStyle = new DataGridViewCellStyle(dataGridView1.Columns[1].DefaultCellStyle);

            // Fill data grid view
            UpdateUIFromTable();
            ValidateAllCells();
            UpdateColumnsVisibility();
        }
        #endregion

        #region Event handlers
        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                UpdateTableRowFromUI(e.RowIndex);
                m_params.SetVoltagesTable();
                m_params.m_generalTab.m_lblRefreshTime_Update(null, null);

                if (NeedSync(e.ColumnIndex))
                {
                    m_params.m_generalTab.SyncTables();
                    //byg m_params.m_currentsTab.UpdateUIFromTable();
                    //byg m_params.SetCurrentsTable();
                }

                ValidateRow(e);

                //if (e.ColumnIndex == colInputScalingFactor.Index)
                //{
                //    m_params.m_currentsTab.ValidateRow(e.RowIndex);
               // }
            }
        }

        public void ValidateRow(int rowIndex)
        {
            ValidateRow(new DataGridViewCellEventArgs(colInputScalingFactor.Index, rowIndex));
        }

        private void ValidateRow(DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != colConverterName.Index) // do not check when converter name changed
            {
                string errorMessage = string.Empty;

                // Range check
                bool rangeIsValid = true;
                for (int i = 0; i < m_rangeCheckCols.Count; i++)
                {
                    errorMessage = RangeCheck(e.RowIndex, m_rangeCheckCols[i]);
                    if (errorMessage != string.Empty)
                        rangeIsValid = false;
                    m_voltagesTableErrors[e.RowIndex].SetValue(errorMessage, m_rangeCheckCols[i]);
                }
                if (rangeIsValid)
                {
                    // Range is OK. Do sanity check
                    for (int i = 0; i < m_sanityCheckCols.Count; i++)
                    {
                        errorMessage = SanityCheck(e.RowIndex, m_sanityCheckCols[i]);
                        m_voltagesTableErrors[e.RowIndex].SetValue(errorMessage, m_sanityCheckCols[i]);
                    }
                }
            }
        }

        private void dataGridView1_CurrentCellDirtyStateChanged_1(object sender, EventArgs e)
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
            //string voltageMeasurementType;
            m_dataGridRowCount = m_params.NumConverters;
            dataGridView1.Rows.Clear();

            while (m_dataGridRowCount > m_params.VoltagesTable.Count)
            {
                m_params.VoltagesTable.Add(new CyVoltagesTableRow());
            }
            for (int i = 0; i < m_dataGridRowCount; i++)
            {

                object[] row = new object[] { 
                    CyVoltagesTableRow.GetConverterNumber(i), 
                    m_params.VoltagesTable[i].m_converterName, 
                    m_params.VoltagesTable[i].m_nominalOutputVoltage, 
                    m_params.VoltagesTable[i].m_minAcqTime_ns,  
                    m_params.VoltagesTable[i].m_uvFaultTreshold,
                    m_params.VoltagesTable[i].m_uvWarningTreshold,
                    m_params.VoltagesTable[i].m_ovWarningTreshold,
                    m_params.VoltagesTable[i].m_ovFaultTreshold,
                    m_params.VoltagesTable[i].m_inputScalingFactor
                };

                dataGridView1.Rows.Add(row);

            }

            UpdateColumnsState();
            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateTableFromUI()
        {
            for (int i = 0; i < m_dataGridRowCount; i++)
                UpdateTableRowFromUI(i);
        }

        public void UpdateTableRowFromUI(int i)
        {
            if (i >= 0 && i < m_dataGridRowCount)
            {
                m_params.VoltagesTable[i].m_converterName = CyParameters.CellToString(dataGridView1.Rows[i].Cells[
                    colConverterName.Index].Value);

                m_params.VoltagesTable[i].m_nominalOutputVoltage = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colNominalOutputVoltage.Index].Value);

                m_params.VoltagesTable[i].m_minAcqTime_ns = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colAcqTime.Index].Value);

                m_params.VoltagesTable[i].m_uvFaultTreshold = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colUVFaultThreshold.Index].Value);

                m_params.VoltagesTable[i].m_uvWarningTreshold = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colUVWarningThreshold.Index].Value);

                m_params.VoltagesTable[i].m_ovFaultTreshold = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colOVFaultThreshold.Index].Value);

                m_params.VoltagesTable[i].m_ovWarningTreshold = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colOVWarningThreshold.Index].Value);

                m_params.VoltagesTable[i].m_inputScalingFactor = CyParameters.ParseNullableDouble(
                    dataGridView1.Rows[i].Cells[colInputScalingFactor.Index].Value);
            }
        }

        private bool NeedSync(int colIndex)
        {
            string colName = dataGridView1.Columns[colIndex].Name;
            return (colName == colConverterName.Name || colName == colNominalOutputVoltage.Name);
        }

        public void SelectDataGridViewRows(int fromRow, int toRow)
        {
            SelectRows(dataGridView1, fromRow, toRow);
        }

        public void UpdateColumnsState()
        {
            CyParameters.SetColumnReadOnlyState(dataGridView1, colOVFaultThreshold.Index, !m_params.FaultSourcesOV);
            CyParameters.SetColumnReadOnlyState(dataGridView1, colOVWarningThreshold.Index,
                !m_params.WarningSourcesOV);
            CyParameters.SetColumnReadOnlyState(dataGridView1, colUVFaultThreshold.Index, !m_params.FaultSourcesUV);
            CyParameters.SetColumnReadOnlyState(dataGridView1, colUVWarningThreshold.Index,
                !m_params.WarningSourcesUV);
        }

        public void UpdateColumnsVisibility()
        {
            colUVFaultThreshold.Visible = m_params.FaultSourcesUV;
            colUVWarningThreshold.Visible = m_params.WarningSourcesUV;
            colOVFaultThreshold.Visible = m_params.FaultSourcesOV;
            colOVWarningThreshold.Visible = m_params.WarningSourcesOV;
        }
        #endregion

        #region Validation
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

        private string RangeCheck(int rowIndex, int colIndex)
        {
            string columnName = dataGridView1.Columns[colIndex].Name;
            double min;
            double max;
            string message = string.Empty;

            if (columnName == colNominalOutputVoltage.Name)
            {
                min = CyParamRanges.NOMINAL_OUTPUT_VOLTAGE_MIN;
                max = CyParamRanges.NOMINAL_OUTPUT_VOLTAGE_MAX;
                message = Resources.NominalOutputVoltageError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colAcqTime.Name)
            {
                min = UInt16.MinValue;
                max = UInt16.MaxValue;
                message = Resources.errAcquisitionTime;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colUVFaultThreshold.Name && m_params.FaultSourcesUV)
            {
                min = CyParamRanges.UV_FAULT_TRESHOLD_MIN;
                max = CyParamRanges.UV_FAULT_TRESHOLD_MAX;
                message = Resources.UvFaultthresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colUVWarningThreshold.Name && m_params.WarningSourcesUV)
            {
                min = CyParamRanges.UV_WARNING_TRESHOLD_MIN;
                max = CyParamRanges.UV_WARNING_TRESHOLD_MAX;
                message = Resources.UvWarningthresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colOVWarningThreshold.Name && m_params.WarningSourcesOV)
            {
                min = CyParamRanges.OV_WARNING_TRESHOLD_MIN;
                max = CyParamRanges.OV_WARNING_TRESHOLD_MAX;
                message = Resources.OvWarningthresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colOVFaultThreshold.Name && m_params.FaultSourcesOV)
            {
                min = CyParamRanges.OV_FAULT_TRESHOLD_MIN;
                max = CyParamRanges.OV_FAULT_TRESHOLD_MAX;
                message = Resources.OvFaultthresholdError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                         string.Empty : string.Format(message, min, max);
            }
            else if (columnName == colInputScalingFactor.Name)
            {
                min = CyParamRanges.INPUT_SCALING_FACTOR_MIN;
                max = CyParamRanges.INPUT_SCALING_FACTOR_MAX;
                message = Resources.InputScalingFactorError;
                message = (CyParameters.IsCellValueValid(dataGridView1, rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }

            return message;
        }

        private string SanityCheck(int rowIndex, int colIndex)
        {
            string message = string.Empty;
            double? uvFaultThreshold = 0;
            double? uvWarningThreshold = 0;
            double? nominalOutVoltage = 0;
            double? ovWarningThreshold = 0;
            double? ovFaultThreshold = 0;
            double? scale = 0;
            try
            {

                uvFaultThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colUVFaultThreshold.Index].Value);
                uvWarningThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colUVWarningThreshold.Index].Value);
                nominalOutVoltage = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colNominalOutputVoltage.Index].Value);
                ovWarningThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colOVWarningThreshold.Index].Value);
                ovFaultThreshold = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colOVFaultThreshold.Index].Value);
                scale = CyParameters.ParseNullableDouble(dataGridView1.Rows[rowIndex].Cells[
                    colInputScalingFactor.Index].Value);

                //UVFault[x] <= UVWarn[x] <= VNom[x] <= OVWarn[x] <= OVFault[x].
                if (dataGridView1.Columns[colIndex].Name == colUVFaultThreshold.Name && m_params.FaultSourcesUV)
                {
                    if (uvFaultThreshold != null)
                    {
                        // Check UV fault threshold
                        //UVFault[x] <= UVWarn[x]
                        message = Resources.UvFaultSanityCheck;
                        if (uvFaultThreshold > uvWarningThreshold && m_params.WarningSourcesUV)
                        {
                            dataGridView1.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }

                        //UVFault[x] multiplied by Scale[x] is >= 50 mV
                        if ((uvFaultThreshold * scale) < CyParamRanges.UV_FAULT_MULT_SCALE_MIN)
                        {
                            message = string.Format(Resources.UvFaultMultScaleSanityCheck,
                                CyParamRanges.UV_FAULT_MULT_SCALE_MIN);
                            dataGridView1.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }
                    }
                }
                else if (dataGridView1.Columns[colIndex].Name == colUVWarningThreshold.Name && m_params.WarningSourcesUV)
                {
                    if (uvWarningThreshold != null)
                    {
                        // Check UV warning threshold
                        //UVWarn[x] <= VNom[x]
                        message = Resources.UvWarningSanityCheck;
                        if (uvWarningThreshold > nominalOutVoltage)
                        {
                            dataGridView1.Rows[rowIndex].Cells[colUVWarningThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colUVWarningThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }
                    }
                }
                else if (dataGridView1.Columns[colIndex].Name == colOVWarningThreshold.Name && m_params.WarningSourcesOV)
                {
                    if (ovWarningThreshold != null)
                    {
                        // Check OV warning threshold
                        //VNom[x] <= OVWarn[x]
                        message = Resources.OvWarningSanityCheck;
                        if (ovWarningThreshold < nominalOutVoltage)
                        {
                            dataGridView1.Rows[rowIndex].Cells[colOVWarningThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colOVWarningThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }
                    }
                }
                else if (dataGridView1.Columns[colIndex].Name == colOVFaultThreshold.Name && m_params.FaultSourcesOV)
                {
                    if (ovFaultThreshold != null)
                    {
                        // Check OV fault threshold
                        //OVWarn[x] <= OVFault[x]
                        message = Resources.OvFaultSanityCheck;
                        if (ovFaultThreshold < ovWarningThreshold && m_params.WarningSourcesOV)
                        {
                            dataGridView1.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }

                        //OVFault[x] multipled by Scale[x] is <= SEVoltageRange
                        double seVoltageRange = (double) m_params.VrefValue * 2;
                        if ((ovFaultThreshold * scale) > seVoltageRange)
                        {
                            message = string.Format(Resources.OvFaultMultScaleSanityCheck, seVoltageRange);
                            dataGridView1.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = message;
                            return message;
                        }
                        else
                        {
                            dataGridView1.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = string.Empty;
                            message = string.Empty;
                        }
                    }
                }
                else if (dataGridView1.Columns[colIndex].Name == colInputScalingFactor.Name)
                {
                    message = string.Empty;
                    dataGridView1.Rows[rowIndex].Cells[colInputScalingFactor.Index].ErrorText = message;
                }

            }
            catch (Exception)
            {
                System.Diagnostics.Debug.Assert(false);
            }
            return message;
        }
        #endregion

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
