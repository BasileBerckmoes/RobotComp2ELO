/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TrimMargin_v3_0.Utils;
using TrimMargin_v3_0.Forms;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0.Tabs
{
    public partial class CySummaryTab : CyTabBase, ICyTab
    {
        #region Private fields
        private int m_dataGridRowCount;
        private byte m_previousPWMResolution;
        private List<DataGridViewColumn> m_editableColumns;
        /// <summary>
        /// Object that contains all math used in the component.
        /// </summary>
        private CyMath m_math;

        /// <summary>
        /// This is a map between sanity check type and the column that shows a message in case of error.
        /// </summary>
        private Dictionary<CyESanityCheck, DataGridViewColumn> m_sanityCheckControlsMap;
        #endregion

        #region Constructor(s)
        public CySummaryTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            // Initialize parameters objects
            m_parameters.m_voltagesTab = this;

            m_math = new CyMath(m_parameters);

            // Initialize tool strip
            cyToolStrip1.Initialize(parameters, dgvVoltages);

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip1;
            m_wrapperDataGridView = dgvVoltages;

            // Initialize data grid view
            InitializeDataGrid(dgvVoltages);

            // Initialize combo boxes
            cbControllerMethod.DataSource = Enum.GetValues(typeof(CyEControllerMethod));
            cbPwmImplementation.DataSource = Enum.GetValues(typeof(CyEImplementation));

            // Events subscription
            cbControllerMethod.Format += cbControllerMethod_Format;
            cbPwmImplementation.Format += cbPwmImplementation_Format;
            numPwmResolution.TextChanged += numPWMResolution_TextChanged;
            cbControllerMethod.SelectedIndexChanged += cbControllerMethod_SelectedIndexChanged;
            cbPwmImplementation.SelectedIndexChanged += cbPwmImplementation_SelectedIndexChanged;

            numPwmResolution.Minimum = 0;
            numPwmResolution.Maximum = decimal.MaxValue;

            CyParameters.DGDisabledStyle = dgvVoltages.Columns[0].DefaultCellStyle;
            CyParameters.DGEnabledStyle = dgvVoltages.Columns[1].DefaultCellStyle;
            CyParameters.VoltagesHeader_v3_0 = CyDataGridExtensions.GetColumnNames(dgvVoltages);

            UpdateUI();
        }
        #endregion

        #region Class properties
        public int DataGridFirstSelectedRow
        {
            get { return GetLessSelectedRow(dgvVoltages.SelectedRows); }
        }
        #endregion

        #region ICyTab implementation
        public string TabName
        {
            get { return Resources.SummaryTabName; }
        }

        public void UpdateUI()
        {
            UpdateControlsFromParameters();
            UpdateDataGridFromTable();
            ValidateImplementation();
            ShowColumnsWithErrors(dgvVoltages);
        }
        #endregion

        #region Overrides
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (m_parameters.IsVoltagesTableDefault)
            {
                m_parameters.SetVoltagesTable();
            }
        }
        #endregion

        #region Initialization methods
        private void InitializeDataGrid(DataGridView dgv)
        {
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToResizeRows = false;
            dgv.AllowUserToOrderColumns = false;
            dgv.AllowUserToResizeColumns = false;
            dgv.EditMode = DataGridViewEditMode.EditOnEnter;
            dgv.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            CyDataGridExtensions.SetColumnSortMode(dgv, DataGridViewColumnSortMode.NotSortable);

            // Map columns that requires validation to row field type.
            colNominalOutputVoltage.Tag = CyEFields.NominalVoltage;
            colMinVoltage.Tag = CyEFields.MinVoltage;
            colMaxVoltage.Tag = CyEFields.MaxVoltage;
            colStartupVoltage.Tag = CyEFields.StartupVoltage;
            colMarginLowPercent.Tag = CyEFields.MarginLowPercent;
            colMarginHighPercent.Tag = CyEFields.MarginHighPercent;
            colCalcMarginLow.Tag = CyEFields.MarginLow;
            colCalcMarginHigh.Tag = CyEFields.MarginHigh;
            colControlSampleTime.Tag = CyEFields.ControlSampleTime;
            colVhPWMOutput.Tag = CyEFields.VhPwmOutput;
            colVAdj.Tag = CyEFields.Vadj;
            colR1.Tag = CyEFields.R1;
            colR2.Tag = CyEFields.R2;
            colR3.Tag = CyEFields.R3;
            colR4.Tag = CyEFields.R4;
            colDesiredVoutRipple.Tag = CyEFields.DesiredVoutRipple;
            colC1.Tag = CyEFields.C1;

            m_editableColumns = new List<DataGridViewColumn>()
            {
                colConverterName,
                colNominalOutputVoltage,
                colMinVoltage,
                colMaxVoltage,
                colStartupVoltage,
                colMarginLowPercent,
                colMarginHighPercent,
                colControlSampleTime,
                colFeedback,
                colVhPWMOutput,
                colVAdj,
                colR1,
                colR2,
                colR3,
                colR4,
                colDesiredVoutRipple,
                colC1
            };

            m_sanityCheckControlsMap = new Dictionary<CyESanityCheck, DataGridViewColumn>()
            {
                { CyESanityCheck.MinVoltageSanity,     colCalcMinVoltage       },
                { CyESanityCheck.MarginLowVoltage,     colCalcMarginLow        },
                { CyESanityCheck.NominalOutputVoltage, colNominalOutputVoltage },
                { CyESanityCheck.MarginHighVoltage,    colCalcMarginHigh       },
                { CyESanityCheck.MinVoltageToVStartup, colStartupVoltage       },
                { CyESanityCheck.VStartupToMaxVoltage, colStartupVoltage       }
            };
        }
        #endregion

        #region Event Handlers
        private void numPWMResolution_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentControl = (NumericUpDown)sender;
            byte value = 0;
            try
            {
                value = Byte.Parse(currentControl.Text);

                if (value < CyConstants.PWM_RESOLUTION_MIN || value > CyConstants.PWM_RESOLUTION_MAX)
                    throw new FormatException();
                ClearError(currentControl);
            }
            catch (FormatException)
            {
                SetError(currentControl, String.Format(Resources.NumPWMResolutionError,
                    CyConstants.PWM_RESOLUTION_MIN, CyConstants.PWM_RESOLUTION_MAX));
            }
            m_parameters.PWMResolution = value;

            // Do not allow to change table if not edit mode
            if (m_parameters.GlobalEditMode == false) return;

            if (!HasError(currentControl))
            {
                if (m_previousPWMResolution >= CyConstants.PWM_RESOLUTION_MIN &&
                        m_previousPWMResolution <= CyConstants.PWM_RESOLUTION_MAX)
                {
                    if (value != m_previousPWMResolution)
                    {
                        UpdateDataGridFromTable();
                    }
                }
            }
            m_previousPWMResolution = value;
        }

        private void cbPwmImplementation_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.PwmImplementation = (CyEImplementation)cbPwmImplementation.SelectedItem;
            ValidateImplementation();
        }

        private void cbControllerMethod_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.ControllerMethod = (CyEControllerMethod)cbControllerMethod.SelectedItem;
            ToggleControlSampleTime();
        }

        private void cbPwmImplementation_Format(object sender, ListControlConvertEventArgs e)
        {
            CyEImplementation item = (CyEImplementation)e.ListItem;
            e.Value = CyEnumExtensions.ToDisplayName(item);
        }

        private void cbControllerMethod_Format(object sender, ListControlConvertEventArgs e)
        {
            CyEControllerMethod item = (CyEControllerMethod)e.ListItem;
            e.Value = CyEnumExtensions.ToDisplayName(item);
        }
        #endregion

        #region Data grid events
        private void dgvVoltages_SelectionChanged(object sender, EventArgs e)
        {
            cyToolStrip1.ChangeCopyPasteEnabling(dgvVoltages.SelectedRows.Count > 0);
            ToggleDeleteConvertorButton();
            ToggleConfigureConvertorButton();
        }

        private void dgvVoltages_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            e.Cancel = true;
            DeleteSelectedRows();
        }

        private void dgvVoltages_DoubleClick(object sender, EventArgs e)
        {
            ConfigureConverter(dgvVoltages.SelectedCells[0].RowIndex);
        }
        #endregion

        #region Validation
        public void ValidateTable()
        {
            bool prevEditMode = m_parameters.GlobalEditMode;
            m_parameters.GlobalEditMode = false;

            ClearTableErrors(dgvVoltages);

            for (int i = 0; i < m_parameters.NumConverters; i++)
            {
                ValidateRow(i);
            }

            m_parameters.GlobalEditMode = prevEditMode;
        }

        private void ValidateRow(int rowIndex)
        {
            bool isOk = RangeCheck(rowIndex);
            if (isOk)
            {
                SanityCheck(rowIndex);
            }
        }

        private bool RangeCheck(int rowIndex)
        {
            bool isOk = true;
            CyCustErr voltError = CyCustErr.Ok;
            CyCustErr hwError = CyCustErr.Ok;

            foreach (DataGridViewColumn item in m_editableColumns)
            {
                // If tag is not assigned, the column does not need validation
                if (item.Tag == null)
                    continue;

                CyEFields field = (CyEFields)item.Tag;
                DataGridViewCell cell = dgvVoltages.Rows[rowIndex].Cells[item.Index];

                if (field == CyEFields.MarginLowPercent)
                {
                    // Margin low percent value is calculated in real time and the value from the grid should be used
                    double? cellValue = CyHelper.ParseNullableDouble(CyHelper.CellToString(cell.Value));
                    voltError = m_parameters.VoltagesTable[rowIndex].ValidateRange(field, cellValue);
                }
                else if (field == CyEFields.MarginHighPercent)
                {
                    // Margin low percent value is calculated in real time and the value from the grid should be used
                    double? cellValue = CyHelper.ParseNullableDouble(CyHelper.CellToString(cell.Value));
                    voltError = m_parameters.VoltagesTable[rowIndex].ValidateRange(field, cellValue);
                }
                else
                {
                    voltError = m_parameters.VoltagesTable[rowIndex].ValidateRange(field);
                    hwError = m_parameters.HardwareTable[rowIndex].ValidateRange(field);
                }

                cell.ErrorText = String.Empty;
                if (voltError.IsNotOk)
                {
                    cell.ErrorText = voltError.Message;
                    isOk = false;
                }
                else if (hwError.IsNotOk)
                {
                    cell.ErrorText = hwError.Message;
                    isOk = false;
                }
            }

            return isOk;
        }

        private bool SanityCheck(int rowIndex)
        {
            bool isOk = true;
            double? calcMinVoltage = m_math.GetCalculatedVMin(rowIndex);
            double? calcMaxVoltage = m_math.GetCalculatedVMax(rowIndex);

            Dictionary<CyESanityCheck, CyCustErr> errors =
                m_parameters.VoltagesTable[rowIndex].SanityCheck(calcMinVoltage, calcMaxVoltage);

            foreach (KeyValuePair<CyESanityCheck, CyCustErr> item in errors)
            {
                if (m_sanityCheckControlsMap.ContainsKey(item.Key) == false)
                    continue;

                if (item.Value.IsNotOk)
                {
                    DataGridViewColumn column = m_sanityCheckControlsMap[item.Key];
                    DataGridViewCell cell = dgvVoltages.Rows[rowIndex].Cells[column.Index];
                    cell.ErrorText = item.Value.Message;
                }
                isOk &= item.Value.IsOk;
            }

            return isOk;
        }

        private void ClearTableErrors(DataGridView dgv)
        {
            for (int i = 0; i < dgv.Columns.Count; i++)
            {
                for (int j = 0; j < dgv.Rows.Count; j++)
                {
                    dgv[i, j].ErrorText = String.Empty;
                }
            }
        }

        public void ValidateImplementation()
        {
            SetError(cbPwmImplementation, CyErrors.GetImplementationError(m_parameters));
        }
        #endregion

        public void UpdateClockDependedValues(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            if (m_parameters == null) return;
            UpdateDataGridFromTable();
        }

        public void UpdateControlsFromParameters()
        {
            lblNumConvertersValue.Text = m_parameters.NumConverters.ToString();
            numPwmResolution.Value = m_parameters.PWMResolution;
            m_previousPWMResolution = m_parameters.PWMResolution;
            cbControllerMethod.SelectedItem = m_parameters.ControllerMethod;
            cbPwmImplementation.SelectedItem = m_parameters.PwmImplementation;

            cyToolStrip1.ToggleAddConverter();
        }

        private void UpdateColumnsVisibilityFromUI()
        {
            m_parameters.ColumnsVisibility = new List<CyColumnsVisibility>();

            foreach (DataGridViewColumn col in dgvVoltages.Columns)
            {
                m_parameters.ColumnsVisibility.Add(new CyColumnsVisibility(col.Name, col.Visible));
            }

            m_parameters.SetIsColumnsVisible();
        }

        private void UpdateColumnsVisibilityFromParam()
        {
            if (m_parameters.ColumnsVisibility == null)
            {
                UpdateColumnsVisibilityFromUI();
                return;
            }

            foreach (DataGridViewColumn col in dgvVoltages.Columns)
            {
                for (int i = 0; i < m_parameters.ColumnsVisibility.Count; i++)
                {
                    if (col.Name == m_parameters.ColumnsVisibility[i].ColumnName)
                    {
                        col.Visible = m_parameters.ColumnsVisibility[i].Visible;
                    }
                }

                // Initialize a state of m_prevControlSampleTimeVisibility
                if (col == colControlSampleTime)
                {
                    m_prevControlSampleTimeVisibility = col.Visible;
                }
            }

            ToggleControlSampleTime();
        }

        public void UpdateDataGridFromTable()
        {
            bool prevGEM = m_parameters.GlobalEditMode;
            m_parameters.GlobalEditMode = false;

            bool dgSizeNeedsUpdate = false;
            m_dataGridRowCount = m_parameters.NumConverters;

            if (dgvVoltages.Rows.Count != m_parameters.NumConverters)
                dgSizeNeedsUpdate = true;

            dgvVoltages.Rows.Clear();
            dgvVoltages.Rows.Add(m_dataGridRowCount);

            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                UpdateDataGridRow(i);
            }

            if (dgSizeNeedsUpdate)
            {
                CyDataGridExtensions.UpdateHeight(dgvVoltages);
            }

            UpdatePWMFrequency();

            m_parameters.GlobalEditMode = prevGEM;

            lblNumConvertersValue.Text = m_parameters.NumConverters.ToString();
            UpdateColumnsVisibilityFromParam();

            ValidateTable();
        }

        public void UpdateDataGridRow(int rowIndex)
        {
            m_math.CalculateTableValues(rowIndex);

            dgvVoltages[colConverterOutput.Index, rowIndex].Value = CyVoltagesTableRow.GetVoltageIndexStr(rowIndex + 1);
            dgvVoltages[colConverterName.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].m_converterName;
            dgvVoltages[colNominalOutputVoltage.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].m_nominalVoltage;
            dgvVoltages[colMinVoltage.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].m_minVoltage;
            dgvVoltages[colCalcMinVoltage.Index, rowIndex].Value = m_math.GetCalculatedVMin(rowIndex);
            dgvVoltages[colMaxVoltage.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].m_maxVoltage;
            dgvVoltages[colCalcMaxVoltage.Index, rowIndex].Value = m_math.GetCalculatedVMax(rowIndex);
            dgvVoltages[colStartupVoltage.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].m_startupVoltage;
            dgvVoltages[colMarginLowPercent.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].MarginLowPercentage;
            dgvVoltages[colCalcMarginLow.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].MarginLow;
            dgvVoltages[colMarginHighPercent.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].MarginHighPercentage;
            dgvVoltages[colCalcMarginHigh.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].MarginHigh;
            dgvVoltages[colControlSampleTime.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].ControlSampleTime;
            dgvVoltages[colFeedback.Index, rowIndex].Value = m_parameters.VoltagesTable[rowIndex].Feedback;

            dgvVoltages[colVhPWMOutput.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_vOh;
            dgvVoltages[colVAdj.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_vAdj;
            dgvVoltages[colR1.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_r1;
            dgvVoltages[colR2.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_r2;
            dgvVoltages[colCalcR2.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_calcR2;
            dgvVoltages[colR3.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_r3;
            dgvVoltages[colCalcR3.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_calcR3;
            dgvVoltages[colR4.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_r4;
            dgvVoltages[colCalcR4.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_calcR4;
            dgvVoltages[colDesiredVoutRipple.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_maxRipple;
            dgvVoltages[colCalcVoutRipple.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_calcVRipple;
            dgvVoltages[colC1.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_c1;
            dgvVoltages[colCalcC1.Index, rowIndex].Value = m_parameters.HardwareTable[rowIndex].m_calcC1;
        }

        private void ToggleDeleteConvertorButton()
        {
            if (dgvVoltages.Rows.Count == dgvVoltages.SelectedRows.Count || dgvVoltages.Rows.Count == 1 ||
                dgvVoltages.SelectedRows.Count == 0)
                cyToolStrip1.DeleteConvertorEnable = false;
            else
                cyToolStrip1.DeleteConvertorEnable = true;
        }

        private void ToggleConfigureConvertorButton()
        {
            cyToolStrip1.ConfigureConvertorEnable = (dgvVoltages.SelectedRows.Count == 1);
        }

        private void UpdateCalculatedValues(int rowIndex)
        {
            dgvVoltages[colCalcMinVoltage.Index, rowIndex].Value = m_math.GetCalculatedVMin(rowIndex);
            dgvVoltages[colCalcMaxVoltage.Index, rowIndex].Value = m_math.GetCalculatedVMax(rowIndex);
        }

        bool m_prevControlSampleTimeVisibility = false;
        public void ToggleControlSampleTime()
        {
            switch (m_parameters.ControllerMethod)
            {
                case CyEControllerMethod.Incremental:
                    m_prevControlSampleTimeVisibility = colControlSampleTime.Visible;
                    colControlSampleTime.Visible = false;
                    break;
                case CyEControllerMethod.Integral:
                    colControlSampleTime.Visible = m_prevControlSampleTimeVisibility;
                    break;
                default:
                    Debug.Fail("Unhandled controller method.");
                    break;
            }
        }

        /// <summary>
        /// Updates label "PWM frequency"
        /// </summary>
        private void UpdatePWMFrequency()
        {
            double? pwmFrequency = m_math.GetPWMFrequency();
            if (pwmFrequency.HasValue)
            {
                lblPwmFreqValue.Text = (pwmFrequency.Value / 1000).ToString("f3") + " kHz";
            }
            else
            {
                lblPwmFreqValue.Text = "Unknown";
            }
        }

        public void SelectDataGridViewRows(int fromRow, int toRow)
        {
            CyDataGridExtensions.SelectRows(dgvVoltages, fromRow, toRow);
        }

        public void DeleteSelectedRows()
        {
            if (dgvVoltages.Rows.Count == dgvVoltages.SelectedRows.Count)
                return;

            int selectedRow = -1;
            List<CyVoltagesTableRow> listVoltagesRows = new List<CyVoltagesTableRow>();
            List<CyHardwareTableRow> listHardwareRows = new List<CyHardwareTableRow>();

            foreach (DataGridViewRow row in dgvVoltages.SelectedRows)
            {
                if (selectedRow < 0 || selectedRow > row.Index)
                    selectedRow = row.Index;

                listVoltagesRows.Add(m_parameters.VoltagesTable[row.Index]);
                listHardwareRows.Add(m_parameters.HardwareTable[row.Index]);
            }

            for (int i = 0; i < listVoltagesRows.Count; i++)
            {
                m_parameters.VoltagesTable.Remove(listVoltagesRows[i]);
                m_parameters.HardwareTable.Remove(listHardwareRows[i]);
            }
            m_parameters.NumConverters = (byte)m_parameters.HardwareTable.Count;

            m_parameters.SetVoltagesTable();
            m_parameters.SetHardwareTable();
            m_parameters.m_voltagesTab.UpdateDataGridFromTable();
            m_parameters.m_voltagesTab.ValidateTable();

            selectedRow = (m_parameters.NumConverters <= selectedRow) ? m_parameters.NumConverters - 1 : selectedRow;
            CyDataGridExtensions.SelectRows(dgvVoltages, selectedRow, selectedRow);

            lblNumConvertersValue.Text = m_parameters.NumConverters.ToString();
            cyToolStrip1.ToggleAddConverter();
        }

        public void AddConverter()
        {
            ConfigureConverter(null);
        }

        public void ConfigureConverter(int? converterNumber)
        {
            int rowIndex = converterNumber.HasValue ? converterNumber.Value : dgvVoltages.RowCount;
            using (CyConfigDialog dialog = new CyConfigDialog(m_parameters, m_editableColumns, rowIndex))
            {
                EventHandler<EventArgs> handler = (sender, e) => UpdateDataGrid();
                dialog.ApplyButtonClick += handler;
                dialog.ShowDialog();
                dialog.ApplyButtonClick -= handler;
            }
            UpdateDataGrid();
        }

        private void UpdateDataGrid()
        {
            List<int> selectedRowsIndexes = new List<int>(CyDataGridExtensions.GetSelectedRowsIndexes(dgvVoltages));
            UpdateDataGridFromTable();
            CyDataGridExtensions.SelectRows(dgvVoltages, selectedRowsIndexes);
        }

        public void HideShowColumns()
        {
            List<DataGridViewColumn> grayOutColumns = new List<DataGridViewColumn>();
            List<DataGridViewColumn> notIncludedColumns = new List<DataGridViewColumn>();
            notIncludedColumns.Add(colConverterOutput);

            if (m_parameters.ControllerMethod == CyEControllerMethod.Incremental)
            {
                notIncludedColumns.Add(colControlSampleTime);
            }

            using (CyVisibleColumnsDialog dialog = new CyVisibleColumnsDialog(
                m_parameters.m_voltagesTab.dgvVoltages, notIncludedColumns, grayOutColumns))
            {
                dialog.ShowDialog();
            }
            UpdateColumnsVisibilityFromUI();
        }

        /// <summary>
        /// Sets column visibility to true if any of its rows contains an error.
        /// </summary>
        private void ShowColumnsWithErrors(DataGridView dgv)
        {
            for (int columnIndex = 0; columnIndex < dgv.Columns.Count; columnIndex++)
            {
                bool isError = false;

                for (int rowIndex = 0; rowIndex < dgv.Rows.Count; rowIndex++)
                {
                    isError = dgv.Rows[rowIndex].Cells[columnIndex].ErrorText != String.Empty;
                    if (isError)
                    {
                        break;
                    }
                }

                if (isError)
                {
                    dgv.Columns[columnIndex].Visible = true;
                }
            }

            UpdateColumnsVisibilityFromUI();
        }
    }
}
