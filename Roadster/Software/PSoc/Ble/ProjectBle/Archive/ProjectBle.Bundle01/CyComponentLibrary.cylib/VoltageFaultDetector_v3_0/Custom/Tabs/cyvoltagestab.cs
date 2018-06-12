/*******************************************************************************
* Copyright 2012 - 2015, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Diagnostics;

namespace VoltageFaultDetector_v3_0
{
    public partial class CyVoltagesTab : CyEditingWrapperControl
    {
        private int m_dataGridRowCount;
        private DataGridViewCellStyle m_disabledStyle;

        #region Class properties
        public override string TabName
        {
            get { return CyCustomizer.VOLTAGE_TAB_NAME; }
        }

        public int DataGridRowCount
        {
            get { return m_dataGridRowCount; }
            set
            {
                m_dataGridRowCount = value;
                dgvVoltages.RowCount = m_dataGridRowCount;
            }
        }

        public int DataGridActiveRowIndex
        {
            get { return dgvVoltages.CurrentRow.Index; }
        }

        public string ColNameVoltageName
        {
            get { return colVoltageName.Name; }
        }

        public string ColNameNominalVoltage
        {
            get { return colNominalVoltage.Name; }
        }

        public string ColNamelInputScalingFactor
        {
            get { return colInputScalingFactor.Name; }
        }

        public string ColNamelUVFaultThreshold
        {
            get { return colUVFaultThreshold.Name; }
        }

        public string ColNamelOVFaultThreshold
        {
            get { return colOVFaultThreshold.Name; }
        }

        public string ColNamelOVFaultActualThreshold
        {
            get { return colOVFaultActualThreshold.Name; }
        }

        public string ColNamelUVFaultActualThreshold
        {
            get { return colUVFaultActualThreshold.Name; }
        }
        #endregion

        #region Constructor(s)
        public CyVoltagesTab(CyParameters param)
            : base()
        {
            // Initialize parameters objects
            m_params = param;
            m_params.VoltagesTab = this;

            InitializeComponent();

            m_disabledStyle = new DataGridViewCellStyle();
            m_disabledStyle.BackColor = SystemColors.ControlLight;

            // Initialize toolstrip
            cyToolStrip1.SetParameters(param);
            cyToolStrip1.m_dgv = dgvVoltages;

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip1;
            m_wrapperDataGridView = dgvVoltages;

            // Initialize data grid view
            dgvVoltages.EditMode = DataGridViewEditMode.EditOnEnter;

            // Prevent data grid from sorting
            foreach (DataGridViewColumn item in dgvVoltages.Columns)
                item.SortMode = DataGridViewColumnSortMode.NotSortable;

            // Fill data grid view
            UpdateUIFromTable();
        }
        #endregion

        #region dgvVoltages events
        private void dgvVoltages_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && dgvVoltages[e.ColumnIndex, e.RowIndex].ReadOnly)
                return;

            if (m_params.GlobalEditMode)
            {
                UpdateTableFromUI();
                m_params.SetVoltagesTable();

                if ((e.ColumnIndex == colNominalVoltage.Index) || (e.ColumnIndex == colUVFaultThreshold.Index) ||
                    (e.ColumnIndex == colOVFaultThreshold.Index) || (e.ColumnIndex == colInputScalingFactor.Index))
                {
                    ValidateRow(e.RowIndex);
                }

                if (e.ColumnIndex == colUVFaultThreshold.Index)
                {
                    UpdateUVfaultActualThreshold(e.RowIndex);
                }

                else if (e.ColumnIndex == colOVFaultThreshold.Index)
                {
                    UpdateOVfaultActualThreshold(e.RowIndex);
                }

                else if (e.ColumnIndex == colInputScalingFactor.Index)
                {
                    UpdateUVfaultActualThreshold(e.RowIndex);
                    UpdateOVfaultActualThreshold(e.RowIndex);
                }
            }
        }

        public void UpdateUVOVfaultActualThreshold()
        {
            for (int i = 0; i < m_params.NumVoltages; i++)
            {
                UpdateUVfaultActualThreshold(i);
                UpdateOVfaultActualThreshold(i);
            }            
        }

        public double CalculateActualThreshold(double faultValue, double scalingFactor)
        {
            double dacRange = (m_params.DACRange == CyDACRangeType.V1) ? CyParamRanges.DAC_1V_MV_LSB :
                                                                         CyParamRanges.DAC_4V_MV_LSB;
            double dacValue = Math.Truncate(Math.Truncate(CyParameters.TrimToMilliVolts(faultValue).Value * 1000 *
                CyParameters.TrimToMilliVolts(scalingFactor).Value + 0.5 * dacRange) / dacRange);

            return (Math.Truncate(((dacValue * dacRange) / (CyParameters.TrimToMilliVolts(scalingFactor).Value * 1000))
                * 1000) / 1000);
        }

        public void UpdateUVfaultActualThreshold(int rowIndex)
        {
            if (m_params.CompareType != CyCompareType.OV)
            {
                if (m_params.ExternalRef)
                {
                    dgvVoltages[colUVFaultActualThreshold.Index, rowIndex].Value =
                        dgvVoltages[colUVFaultThreshold.Index, rowIndex].Value;
                }
                else if (m_params.VoltagesTable[rowIndex].UvFaultThreshold.HasValue &&
                    m_params.VoltagesTable[rowIndex].InputScalingFactor.HasValue)
                {
                    dgvVoltages[colUVFaultActualThreshold.Index, rowIndex].Value =
                        CalculateActualThreshold(m_params.VoltagesTable[rowIndex].UvFaultThreshold.Value,
                        m_params.VoltagesTable[rowIndex].InputScalingFactor.Value);
                }
                else
                {
                    dgvVoltages[colUVFaultActualThreshold.Index, rowIndex].Value = null;
                }
            }
        }

        public void UpdateOVfaultActualThreshold(int rowIndex)
        {
            if (m_params.CompareType != CyCompareType.UV)
            {
                if (m_params.ExternalRef)
                {
                    dgvVoltages[colOVFaultActualThreshold.Index, rowIndex].Value =
                        dgvVoltages[colOVFaultThreshold.Index, rowIndex].Value;
                }
                else if (m_params.VoltagesTable[rowIndex].OvFaultThreshold.HasValue &&
                    m_params.VoltagesTable[rowIndex].InputScalingFactor.HasValue)
                {
                    dgvVoltages[colOVFaultActualThreshold.Index, rowIndex].Value =
                        CalculateActualThreshold(m_params.VoltagesTable[rowIndex].OvFaultThreshold.Value,
                        m_params.VoltagesTable[rowIndex].InputScalingFactor.Value);
                }
                else
                {
                    dgvVoltages[colOVFaultActualThreshold.Index, rowIndex].Value = null;
                }
            }
        }

        private void dgvVoltages_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(dgvVoltages);
        }

        private void dgvVoltages_SelectionChanged(object sender, EventArgs e)
        {
            cyToolStrip1.ChangeCopyPasteEnabling(dgvVoltages.SelectedRows.Count > 0);
        }

        private void dgvVoltages_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if ((e.ColumnIndex == colNominalVoltage.Index) || (e.ColumnIndex == colUVFaultThreshold.Index) ||
                (e.ColumnIndex == colOVFaultThreshold.Index) || (e.ColumnIndex == colUVFaultActualThreshold.Index) ||
                (e.ColumnIndex == colOVFaultActualThreshold.Index) || (e.ColumnIndex == colInputScalingFactor.Index))
            {
                try
                {
                    string format = "N3";
                    e.Value = Double.Parse(e.Value.ToString()).ToString(format);
                }
                catch
                {
                }
            }
        }
        #endregion dgvVoltages events

        #region Validation
        public bool ValidateAllTable()
        {
            bool prev_edit_mode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            bool isOk = true;
            for (int i = 0; i < m_params.NumVoltages; i++)
            {
                isOk &= ValidateRow(i);
            }
            m_params.GlobalEditMode = prev_edit_mode;
            return isOk;
        }

        private bool ValidateRow(int rowIndex)
        {
            bool isOk = true;
            // Range check
            isOk &= RangeCheck(rowIndex, colNominalVoltage.Index);
            isOk &= RangeCheck(rowIndex, colUVFaultThreshold.Index);
            isOk &= RangeCheck(rowIndex, colOVFaultThreshold.Index);
            isOk &= RangeCheck(rowIndex, colInputScalingFactor.Index);
            if (isOk)
            {
                isOk = SanityCheck(rowIndex);
            }
            return isOk;
        }

        private bool RangeCheck(int rowIndex, int colIndex)
        {
            double min;
            double max;
            string message = string.Empty;

            if (colIndex == colNominalVoltage.Index)
            {
                min = CyParamRanges.NOMINAL_VOLTAGE_MIN;
                max = CyParamRanges.NOMINAL_VOLTAGE_MAX;
                message = Resources.NominalOutputVoltageError;
                message = (IsValueInRange(rowIndex, colIndex, min, max, message)) ? 
                    string.Empty : string.Format(message, min, max);
            }
            else if ((colIndex == colUVFaultThreshold.Index) && (colUVFaultThreshold.ReadOnly == false))
            {
                min = CyParamRanges.UV_FAULT_THRESHOLD_MIN;
                max = CyParamRanges.UV_FAULT_THRESHOLD_MAX;
                message = Resources.UvFaultThresholdError;
                message = (IsValueInRange(rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if ((colIndex == colOVFaultThreshold.Index) && (colOVFaultThreshold.ReadOnly == false))
            {
                min = CyParamRanges.OV_FAULT_THRESHOLD_MIN;
                max = CyParamRanges.OV_FAULT_THRESHOLD_MAX;
                message = Resources.OvFaultThresholdError;
                message = (IsValueInRange(rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }
            else if ((colIndex == colInputScalingFactor.Index) && (colInputScalingFactor.ReadOnly == false))
            {
                min = CyParamRanges.INPUT_SCALING_FACTOR_MIN;
                max = CyParamRanges.INPUT_SCALING_FACTOR_MAX;
                message = Resources.InputScalingFactorError;
                message = (IsValueInRange(rowIndex, colIndex, min, max, message)) ?
                    string.Empty : string.Format(message, min, max);
            }

            return String.IsNullOrEmpty(message);
        }

        private bool IsValueInRange(int rowIndex, int colIndex, double min, double max, string errorMessage)
        {
            bool isCellValid = false;
            string message = string.Format(errorMessage, min, max);
            try
            {
                double? currCellValue = null;
                if (colIndex == colNominalVoltage.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].NominalVoltage;
                else if (colIndex == colUVFaultThreshold.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].UvFaultThreshold;
                else if (colIndex == colOVFaultThreshold.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].OvFaultThreshold;
                else if (colIndex == colUVFaultActualThreshold.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].UvFaultActualThreshold;
                else if (colIndex == colOVFaultActualThreshold.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].OvFaultActualThreshold;
                else if (colIndex == colInputScalingFactor.Index)
                    currCellValue = m_params.VoltagesTable[rowIndex].InputScalingFactor;

                if ((currCellValue.HasValue) && (currCellValue < min || currCellValue > max))
                {
                    throw new Exception();
                }
                else if ((currCellValue == null) && (dgvVoltages[colIndex, rowIndex].ReadOnly == false) &&
                         (IsCellEmpty(colIndex, rowIndex) == false))
                {
                    throw new Exception();
                }
                else
                {
                    dgvVoltages[colIndex, rowIndex].ErrorText = string.Empty;
                    isCellValid = true;
                }
            }
            catch (Exception)
            {
                dgvVoltages[colIndex, rowIndex].ErrorText = message;
            }
            return isCellValid;
        }

        private bool SanityCheck(int rowIndex)
        {
            double eps = 0.000001;
            string message = string.Empty;
            bool check1bPassed = true;
            bool check2Passed = true;
            try
            {
                double? nominalVoltage = m_params.VoltagesTable[rowIndex].NominalVoltage;
                double? uvFaultThreshold = m_params.VoltagesTable[rowIndex].UvFaultThreshold;
                double? ovFaultThreshold = m_params.VoltagesTable[rowIndex].OvFaultThreshold;
                double? scale = m_params.VoltagesTable[rowIndex].InputScalingFactor;

                if (IsColumnDisabled(ColNamelInputScalingFactor))
                    scale = 1;

                #region Check1a: UVFault[x] <= VNom[x] <= OVFault[x]
                {
                    message = Resources.VoltagesCompareSanityCheck;

                    if (nominalVoltage.HasValue)
                    {
                        if ((uvFaultThreshold.HasValue && !IsColumnDisabled(ColNamelUVFaultThreshold) && 
                            (nominalVoltage < uvFaultThreshold - eps)) ||
                            (ovFaultThreshold.HasValue && !IsColumnDisabled(ColNamelOVFaultThreshold) &&
                            (nominalVoltage > ovFaultThreshold + eps)))
                        {
                            dgvVoltages.Rows[rowIndex].Cells[colNominalVoltage.Index].ErrorText = message;
                        }
                    }
                    else
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colNominalVoltage.Index].ErrorText = string.Empty;
                        message = string.Empty;
                    }
                }
                #endregion Check1a

                #region Check1b: UVFault[x] <= OVFault[x]
                {
                    message = Resources.VoltagesCompareSanityCheck;

                    if (!nominalVoltage.HasValue && uvFaultThreshold.HasValue && ovFaultThreshold.HasValue)
                    {
                        message = Resources.OvUvVoltagesCompareSanityCheck;

                        if ((!IsColumnDisabled(ColNamelUVFaultThreshold) && !IsColumnDisabled(ColNamelOVFaultThreshold)
                            && (uvFaultThreshold > ovFaultThreshold + eps)))
                        {
                            dgvVoltages.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = message;
                            check1bPassed = false;
                        }
                    }
                    else
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = string.Empty;
                        message = string.Empty;
                    }
                }
                #endregion Check1b
                
                #region Check2: OVFault[x] multipled by Scale[x] is <= DACRange when ExtRef==False
                {
                    message = Resources.OvFaultMultScaleSanityCheck;
                    double dacRange = (m_params.DACRange == CyDACRangeType.V1) ? CyParamRanges.DAC_1V_VOLTAGE :
                                                                                 CyParamRanges.DAC_4V_VOLTAGE;
                    if ((m_params.ExternalRef == false) && ovFaultThreshold.HasValue &&
                        !IsColumnDisabled(ColNamelOVFaultThreshold) && scale.HasValue &&
                        ((ovFaultThreshold * scale) > dacRange + eps))
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = message;
                        check2Passed = false;
                    }
                    else
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = string.Empty;
                        message = string.Empty;
                    }
                }
                #endregion Check2

                #region Check3a: UVFault[x] multiplied by Scale[x] is >= 50 mV
                if (check1bPassed)
                {
                    message = Resources.UvFaultMultScaleSanityCheck;
                    if (uvFaultThreshold.HasValue && !IsColumnDisabled(ColNamelUVFaultThreshold) && 
                        scale.HasValue && ((uvFaultThreshold * scale) < 0.05 - eps))
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = message;
                    }
                    else
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colUVFaultThreshold.Index].ErrorText = string.Empty;
                        message = string.Empty;
                    }
                }
                #endregion Check3a

                #region Check3b: OVFault[x] multiplied by Scale[x] is >= 50 mV
                if (check2Passed)
                {
                    message = Resources.OvLowerLimitCheck;
                    if (ovFaultThreshold.HasValue && 
                        !IsColumnDisabled(ColNamelOVFaultThreshold) && IsColumnDisabled(ColNamelUVFaultThreshold) 
                        && scale.HasValue &&  ((ovFaultThreshold * scale) < 0.05 - eps))
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = message;
                    }
                    else
                    {
                        dgvVoltages.Rows[rowIndex].Cells[colOVFaultThreshold.Index].ErrorText = string.Empty;
                        message = string.Empty;
                    }
                }
                #endregion Check3b

            }
            catch
            {
                Debug.Assert(false);
            }
            return String.IsNullOrEmpty(message);
        }

        public List<string> GetAllDataGridErrors()
        {
            List<string> errorList = new List<string>();
            for (int i = 0; i < dgvVoltages.RowCount; i++)
                for (int j = 0; j < dgvVoltages.ColumnCount; j++)
                {
                    if (String.IsNullOrEmpty(dgvVoltages[j, i].ErrorText) == false)
                    {
                        errorList.Add(dgvVoltages[j, i].ErrorText);
                    }
                }
            return errorList;
        }
        #endregion Validation

        #region Helper functions
        public void UpdateUIFromTable()
        {
            bool prev_edit_mode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            m_dataGridRowCount = m_params.NumVoltages;
            dgvVoltages.Rows.Clear();
            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                dgvVoltages.Rows.Add(new object[] {
                    CyVoltagesTableRow.GetVoltageIndexStr(i+1),
                    m_params.VoltagesTable[i].VoltageName,
                    m_params.VoltagesTable[i].NominalVoltage,
                    m_params.VoltagesTable[i].UvFaultThreshold,
                    m_params.VoltagesTable[i].UvFaultActualThreshold,
                    m_params.VoltagesTable[i].OvFaultThreshold,
                    m_params.VoltagesTable[i].OvFaultActualThreshold,
                    m_params.VoltagesTable[i].InputScalingFactor
                });
            }
            SetColumnsStyle();
            m_params.GlobalEditMode = prev_edit_mode;
        }        

        public void UpdateTableFromUI()
        {
            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                m_params.VoltagesTable[i].VoltageName =
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNameVoltageName].Value);

                m_params.VoltagesTable[i].NominalVoltage = CyParameters.TrimToMilliVolts(CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNameNominalVoltage].Value)));

                m_params.VoltagesTable[i].UvFaultThreshold = CyParameters.TrimToMilliVolts(CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNamelUVFaultThreshold].Value)));                

                m_params.VoltagesTable[i].UvFaultActualThreshold = CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNamelUVFaultActualThreshold].Value));

                m_params.VoltagesTable[i].OvFaultThreshold = CyParameters.TrimToMilliVolts(CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNamelOVFaultThreshold].Value)));

                m_params.VoltagesTable[i].OvFaultActualThreshold = CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNamelOVFaultActualThreshold].Value));

                m_params.VoltagesTable[i].InputScalingFactor = CyParameters.TrimToMilliVolts(CyParameters.ParseNullableDouble(
                    CyParameters.CellToString(dgvVoltages.Rows[i].Cells[ColNamelInputScalingFactor].Value)));                
            }
        }

        #region Disabling columns
        public void SetColumnsStyle()
        {
            bool prev_edit_mode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            switch (m_params.CompareType)
            {
                case CyCompareType.OV:
                    m_params.VoltagesTab.DisableColumn(m_params.VoltagesTab.ColNamelUVFaultActualThreshold);
                    m_params.VoltagesTab.DisableColumn(m_params.VoltagesTab.ColNamelUVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelOVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelOVFaultActualThreshold);
                    break;
                case CyCompareType.UV:
                    m_params.VoltagesTab.DisableColumn(m_params.VoltagesTab.ColNamelOVFaultActualThreshold);
                    m_params.VoltagesTab.DisableColumn(m_params.VoltagesTab.ColNamelOVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelUVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelUVFaultActualThreshold);
                    break;
                case CyCompareType.OV_UV:
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelOVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelUVFaultThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelOVFaultActualThreshold);
                    m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelUVFaultActualThreshold);
                    break;
            }

            if (m_params.ExternalRef)
            {
                m_params.VoltagesTab.DisableColumn(m_params.VoltagesTab.ColNamelInputScalingFactor);
            }
            else
            {
                m_params.VoltagesTab.EnableColumn(m_params.VoltagesTab.ColNamelInputScalingFactor);
            }
            m_params.VoltagesTab.ValidateAllTable();
            m_params.GlobalEditMode = prev_edit_mode;
        }

        private bool IsColumnDisabled(string colName)
        {
            return (dgvVoltages.Columns[colName].ReadOnly);
        }

        private void DisableColumn(string colName)
        {
            if ((colName != ColNamelUVFaultActualThreshold) && (colName != ColNamelOVFaultActualThreshold))
            {
                dgvVoltages.Columns[colName].DefaultCellStyle = m_disabledStyle;
                dgvVoltages.Columns[colName].ReadOnly = true;
            }

            string cellValue = "---";
            if (colName == ColNamelInputScalingFactor)
            {
                cellValue = "1.000";
            }
            for (int i = 0; i < dgvVoltages.RowCount; i++)
            {
                dgvVoltages.Rows[i].Cells[colName].Value = cellValue;
            }
        }

        private void EnableColumn(string colName)
        {
            if ((colName != ColNamelUVFaultActualThreshold) && (colName != ColNamelOVFaultActualThreshold))
            {
                dgvVoltages.Columns[colName].DefaultCellStyle = dgvVoltages.DefaultCellStyle.Clone();
                dgvVoltages.Columns[colName].ReadOnly = false;
            }

            for (int i = 0; i < dgvVoltages.RowCount; i++)
            {
                object cellValue = 0;
                if (colName == ColNamelUVFaultThreshold)
                {
                    cellValue = m_params.VoltagesTable[i].UvFaultThreshold;
                    dgvVoltages.Columns[colName].DefaultCellStyle.Format = "N3";
                }
                else if (colName == ColNamelOVFaultThreshold)
                {
                    cellValue = m_params.VoltagesTable[i].OvFaultThreshold;
                    dgvVoltages.Columns[colName].DefaultCellStyle.Format = "N3";
                }
                else if (colName == ColNamelInputScalingFactor)
                {
                    cellValue = m_params.VoltagesTable[i].InputScalingFactor;
                    dgvVoltages.Columns[colName].DefaultCellStyle.Format = "N3";
                }
                else if (colName == ColNamelUVFaultActualThreshold)
                {
                    UpdateUVfaultActualThreshold(i);
                }
                else if (colName == ColNamelOVFaultActualThreshold)
                {
                    UpdateOVfaultActualThreshold(i);
                }

                if ((colName != ColNamelUVFaultActualThreshold) && (colName != ColNamelOVFaultActualThreshold))
                {
                    dgvVoltages.Rows[i].Cells[colName].Value = cellValue;
                }
            }
        }

        private void ApplyDisabledColValues()
        {
            if (dgvVoltages.Columns[colUVFaultThreshold.Index].ReadOnly)
            {
                for (int i = 0; i < m_params.NumVoltages; i++)
                {
                    m_params.VoltagesTable[i].UvFaultThreshold = null;
                }
            }
            if (dgvVoltages.Columns[colOVFaultThreshold.Index].ReadOnly)
            {
                for (int i = 0; i < m_params.NumVoltages; i++)
                {
                    m_params.VoltagesTable[i].OvFaultThreshold = null;
                }
            }
            if (dgvVoltages.Columns[colInputScalingFactor.Index].ReadOnly)
            {
                for (int i = 0; i < m_params.NumVoltages; i++)
                {
                    m_params.VoltagesTable[i].InputScalingFactor = 1;
                }
            }
        }
        #endregion Disabling columns

        public List<string> GetVoltageColNames()
        {
            List<string> colNames = new List<string>();
            for (int i = 0; i < dgvVoltages.ColumnCount; i++)
            {
                colNames.Add(dgvVoltages.Columns[i].HeaderText);
            }
            return colNames;
        }

        private bool IsCellEmpty(int colIndex, int rowIndex)
        {
            if ((dgvVoltages[colIndex, rowIndex].Value == null) || 
                    ((dgvVoltages[colIndex, rowIndex].Value != null) && 
                    (String.IsNullOrEmpty(dgvVoltages[colIndex, rowIndex].Value.ToString()))))
            {
                return true;
            }
            return false;
        }

        public void SelectRow(int row)
        {
            if ((row >= 0) && (row < dgvVoltages.RowCount))
            {
                dgvVoltages.Rows[row].Selected = true;
                dgvVoltages.CurrentCell = dgvVoltages[0, row];
            }
        }
        #endregion Helper functions

        #region GetErrors()
        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>(base.GetErrors());

            List<string> dataGridErrors = GetAllDataGridErrors();
            if (dataGridErrors.Count > 0)
            {
                errs.Add(new CyCustErr(Resources.DataGridError));
            }
            else
            {
                ApplyDisabledColValues();
            }

            return errs;
        }
        #endregion GetErrors()

        #region ProcessCmdKey override
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            bool result = true;

            if (keyData == (Keys.Control | Keys.M))
            {
                cyToolStrip1.tsbImport_Click(null, EventArgs.Empty);
            }
            else if (keyData == (Keys.Control | Keys.R))
            {
                cyToolStrip1.tsbExport_Click(null, EventArgs.Empty);
            }
            else
            {
                result = base.ProcessCmdKey(ref msg, keyData);
            }

            return result;
        }
        #endregion
    }
}
