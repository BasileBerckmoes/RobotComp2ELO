/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;

namespace I2C_LCD_v1_20
{
    public partial class CyCustomCommandsTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return CyCustomizer.CUSTOM_COMMANDS_TAB_NAME; }
        }

        #region Constants
        private const int STRING_COL_WIDTH = 280;
        private const int DATA_SIZE_COL_WIDTH = 90;
        public const string REQUIRED_COMMANDS = "RequiredCommands";
        #endregion

        #region Variables
        private ContextMenuStrip m_contextMenu;
        #endregion

        #region Constructor(s)
        public CyCustomCommandsTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            // Initialize Required Commands datagrid
            InitializeDataGridView(dgvRequiredCmds);
            dgvRequiredCmds.Tag = REQUIRED_COMMANDS;
            dgvRequiredCmds.AllowUserToAddRows = false;
            dgvRequiredCmds.AllowUserToDeleteRows = false;
            dgvRequiredCmds.RowHeadersVisible = false;
            dgvRequiredCmds.Columns[colReqDataSize.Index].Width = DATA_SIZE_COL_WIDTH;
            dgvRequiredCmds.Columns[colReqCmdDesc.Index].Width = STRING_COL_WIDTH;
            CyParameters.SetColumnReadOnlyState(colReqCmdDesc, true);
            colReqCmdSize.Items.Clear();
            for (int i = CyParamRanges.CMD_SIZE_MIN; i <= CyParamRanges.CMD_SIZE_MAX; i++)
            {
                colReqCmdSize.Items.AddRange(i.ToString());  // initialize drop-down list
            }

            // Initialize Custom Commands datagrid
            InitializeDataGridView(dgvCustomCmds);
            dgvCustomCmds.AllowUserToAddRows = true;
            dgvCustomCmds.AllowUserToDeleteRows = true;
            dgvCustomCmds.RowHeadersVisible = true;
            dgvCustomCmds.Columns[colCustApiName.Index].Width = STRING_COL_WIDTH;
            colCustCmdSize.Items.Clear();
            for (int i = CyParamRanges.CMD_SIZE_MIN; i <= CyParamRanges.CMD_SIZE_MAX; i++)
            {
                colCustCmdSize.Items.AddRange(i.ToString()); // initialize drop-down list
            }

            // Initialize Context Menu
            m_contextMenu = new ContextMenuStrip();
            m_contextMenu.Items.Add(Resources.ContextMenuDeleteItem);
            m_contextMenu.ItemClicked += m_contextMenu_ItemClicked;
        }
        #endregion

        #region Update UI from parameters
        public void UpdateUI()
        {
            UpdateUI(true);
        }
        public void UpdateUI(bool updateDataGrids)
        {
            chbCommandPattern.Checked = m_params.UseCmdPattern;
            if (updateDataGrids)
            {
                UpdateRequiredUIFromTable();
                UpdateCustomUIFromTable();
            }
        }

        public void UpdateRequiredUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            dgvRequiredCmds.Rows.Clear();
            for (int row = 0; row < m_params.RequiredCommands.Count; row++)
            {
                object[] newRow = new object[dgvRequiredCmds.ColumnCount];
                dgvRequiredCmds.Rows.Add(newRow);
                UpdateRequiredUIFromTable(row);
            }
            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateRequiredUIFromTable(int row)
        {
            dgvRequiredCmds[colReqCmdSize.Index, row].Value = m_params.RequiredCommands[row].CmdSize.ToString();
            dgvRequiredCmds[colReqDataSize.Index, row].Value = m_params.RequiredCommands[row].DataSize;
            dgvRequiredCmds[colReqCmdByte1.Index, row].Value = CyParameters.NullableByteToHex(
                                                                          m_params.RequiredCommands[row].CmdByte1);
            dgvRequiredCmds[colReqCmdByte2.Index, row].Value = CyParameters.NullableByteToHex(
                                                                          m_params.RequiredCommands[row].CmdByte2);
            dgvRequiredCmds[colReqCmdByte3.Index, row].Value = CyParameters.NullableByteToHex(
                                                                          m_params.RequiredCommands[row].CmdByte3);
            dgvRequiredCmds[colReqCmdByte4.Index, row].Value = CyParameters.NullableByteToHex(
                                                                          m_params.RequiredCommands[row].CmdByte4);
            dgvRequiredCmds[colReqCmdDesc.Index, row].Value = m_params.RequiredCommands[row].CmdDescription;

            // Set Cursor Position data size column should be editable
            CyParameters.SetCellReadOnlyState(dgvRequiredCmds[colReqDataSize.Index, row],
                                                       m_params.RequiredCommands[row].IsDataSizeReadOnly);
        }

        public void UpdateCustomUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            dgvCustomCmds.Rows.Clear();
            for (int row = 0; row < m_params.CustomCommands.Count; row++)
            {
                object[] newRow = new object[dgvCustomCmds.ColumnCount];
                dgvCustomCmds.Rows.Add(newRow);
                UpdateCustomUIFromTable(row);
            }

            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateCustomUIFromTable(int row)
        {
            dgvCustomCmds[colCustEnable.Index, row].Value = m_params.CustomCommands[row].Enable;
            dgvCustomCmds[colCustCmdSize.Index, row].Value = m_params.CustomCommands[row].CmdSize.ToString();
            dgvCustomCmds[colCustDataSize.Index, row].Value = m_params.CustomCommands[row].DataSize;
            dgvCustomCmds[colCustCmdByte1.Index, row].Value = CyParameters.NullableByteToHex(
                                                                             m_params.CustomCommands[row].CmdByte1);
            dgvCustomCmds[colCustCmdByte2.Index, row].Value = CyParameters.NullableByteToHex(
                                                                             m_params.CustomCommands[row].CmdByte2);
            dgvCustomCmds[colCustCmdByte3.Index, row].Value = CyParameters.NullableByteToHex(
                                                                             m_params.CustomCommands[row].CmdByte3);
            dgvCustomCmds[colCustCmdByte4.Index, row].Value = CyParameters.NullableByteToHex(
                                                                             m_params.CustomCommands[row].CmdByte4);
            dgvCustomCmds[colCustApiName.Index, row].Value = m_params.CustomCommands[row].ApiName;
        }
        #endregion

        #region Update parameters from UI
        public void UpdateRequiredTableFromUI(int row)
        {
            m_params.RequiredCommands[row].CmdSize = CyParameters.ParseNullableByte(
                                                              dgvRequiredCmds[colReqCmdSize.Index, row].Value);
            m_params.RequiredCommands[row].DataSize = CyParameters.ParseNullableByte(
                                                              dgvRequiredCmds[colReqDataSize.Index, row].Value);
            m_params.RequiredCommands[row].CmdByte1 = CyParameters.ParseHexByte(
                                                              dgvRequiredCmds[colReqCmdByte1.Index, row].Value);
            m_params.RequiredCommands[row].CmdByte2 = CyParameters.ParseHexByte(
                                                              dgvRequiredCmds[colReqCmdByte2.Index, row].Value);
            m_params.RequiredCommands[row].CmdByte3 = CyParameters.ParseHexByte(
                                                              dgvRequiredCmds[colReqCmdByte3.Index, row].Value);
            m_params.RequiredCommands[row].CmdByte4 = CyParameters.ParseHexByte(
                                                              dgvRequiredCmds[colReqCmdByte4.Index, row].Value);
        }

        public void UpdateCustomTableFromUI(int row)
        {
            m_params.CustomCommands[row].Enable = CyParameters.CellToBool(
                                                              dgvCustomCmds[colCustEnable.Index, row].Value);
            m_params.CustomCommands[row].CmdSize = CyParameters.ParseNullableByte(
                                                              dgvCustomCmds[colCustCmdSize.Index, row].Value);
            m_params.CustomCommands[row].DataSize = CyParameters.ParseNullableByte(
                                                              dgvCustomCmds[colCustDataSize.Index, row].Value);
            m_params.CustomCommands[row].CmdByte1 = CyParameters.ParseHexByte(
                                                              dgvCustomCmds[colCustCmdByte1.Index, row].Value);
            m_params.CustomCommands[row].CmdByte2 = CyParameters.ParseHexByte(
                                                              dgvCustomCmds[colCustCmdByte2.Index, row].Value);
            m_params.CustomCommands[row].CmdByte3 = CyParameters.ParseHexByte(
                                                              dgvCustomCmds[colCustCmdByte3.Index, row].Value);
            m_params.CustomCommands[row].CmdByte4 = CyParameters.ParseHexByte(
                                                              dgvCustomCmds[colCustCmdByte4.Index, row].Value);
            m_params.CustomCommands[row].ApiName = CyParameters.CellToString(
                                                              dgvCustomCmds[colCustApiName.Index, row].Value);
        }
        #endregion

        #region Data grids event handlers
        private void dgvRequiredCmds_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Set changes
            if (m_params.GlobalEditMode)
            {
                UpdateRequiredTableFromUI(e.RowIndex);
                m_params.SetRequiredCommands();
            }

            // Enable/Disable CMD Byte cells
            if (e.RowIndex < 0) return;
            if (e.ColumnIndex == colReqCmdSize.Index)
            {
                GrayOutCmdByteCells(sender, e);
            }

            if (m_params.GlobalEditMode)
            {
                // Check range
                RangeCheck(sender, e);
            }
        }

        private void dgvCustomCmds_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Set changes
            if (m_params.GlobalEditMode)
            {
                UpdateCustomTableFromUI(e.RowIndex);
                m_params.SetCustomCommands();
            }
            // Enable/Disable CMD Byte cells
            if (e.RowIndex < 0) return;
            if (e.ColumnIndex == colCustCmdSize.Index)
            {
                GrayOutCmdByteCells(sender, e);
            }

            if (m_params.GlobalEditMode)
            {
                // Check range
                RangeCheck(sender, e);

                // Check API name
                if (e.ColumnIndex == colCustApiName.Index)
                {
                    string apiName = CyParameters.CellToString(dgvCustomCmds[e.ColumnIndex, e.RowIndex].Value).Trim();
                    // Check if name is valid
                    if (String.IsNullOrEmpty(apiName) == false &&
                       (System.Text.RegularExpressions.Regex.Match(apiName, @"([A-Za-z0-9_]*)").Length ==
                                                                                                    apiName.Length))
                    {
                        // Name is valid, so check if it is not reserved
                        if (m_params.IsAPINameReserved(apiName))
                        {
                            dgvCustomCmds[e.ColumnIndex, e.RowIndex].ErrorText = String.Format(
                                Resources.APINameReserved, apiName);
                        }
                        else
                        {
                            // Name is not reseved, so check if it is not in uppercase
                            if (apiName == apiName.ToUpper())
                            {
                                dgvCustomCmds[e.ColumnIndex, e.RowIndex].ErrorText = Resources.APINameInUppercase;
                            }
                            else
                            {
                                dgvCustomCmds[e.ColumnIndex, e.RowIndex].ErrorText = String.Empty;
                            }
                        }
                    }
                    else
                    {
                        dgvCustomCmds[e.ColumnIndex, e.RowIndex].ErrorText = Resources.ApiNameInvalid;
                    }
                    // Check names for duplication
                    CheckAPINameDuplicates();
                }
            }
        }

        private void dgv_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (e.Value != null)
            {
                if ((sender == dgvRequiredCmds &&
                    (e.ColumnIndex >= colReqCmdByte1.Index && e.ColumnIndex <= colReqCmdByte4.Index)) ||
                    (sender == dgvCustomCmds &&
                    (e.ColumnIndex >= colCustCmdByte1.Index && e.ColumnIndex <= colCustCmdByte4.Index)))
                {
                    try
                    {
                        e.Value = CyParameters.CellFormatHex(e.Value);
                        e.FormattingApplied = true;
                    }
                    catch { }
                }
            }
        }

        private void dgv_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            if (dataGridView.CurrentCell != null)
            {
                if ((dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell)) ||
                    (dataGridView.CurrentCell.GetType() == typeof(DataGridViewComboBoxCell)))
                {
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
                }
            }
        }

        private void dgvCustomCmds_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                m_params.CustomCommands.Add(new CyCustomCommandRow());
            }
        }

        private void dgvCustomCmds_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                DataGridView.HitTestInfo ht = dgvCustomCmds.HitTest(e.X, e.Y);
                if (ht.RowIndex < dgvCustomCmds.RowCount - 1) // last row is "new row" and cannot be deleted
                {
                    if (ht.Type == DataGridViewHitTestType.RowHeader && dgvCustomCmds.SelectedRows.Count > 0)
                    {
                        m_contextMenu.Show(MousePosition);
                    }
                }
            }
        }

        private void dgvCustomCmds_RowHeaderMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left && e.RowIndex < (dgvCustomCmds.RowCount - 1))
            {
                m_contextMenu_ItemClicked(sender, new ToolStripItemClickedEventArgs(m_contextMenu.Items[0]));
            }
        }
        #endregion

        #region Data grid appearance methods
        private void GrayOutCmdByteCells(object sender, DataGridViewCellEventArgs e)
        {
            DataGridView dgv = (DataGridView)sender;
            int columnCmdByte1Index;
            int columnCmdByte2Index;
            int columnCmdByte3Index;
            int columnCmdByte4Index;
            byte cmdSize = 0;

            if (dgv == dgvRequiredCmds)
            {
                columnCmdByte1Index = colReqCmdByte1.Index;
                columnCmdByte2Index = colReqCmdByte2.Index;
                columnCmdByte3Index = colReqCmdByte3.Index;
                columnCmdByte4Index = colReqCmdByte4.Index;
            }
            else
            {
                columnCmdByte1Index = colCustCmdByte1.Index;
                columnCmdByte2Index = colCustCmdByte2.Index;
                columnCmdByte3Index = colCustCmdByte3.Index;
                columnCmdByte4Index = colCustCmdByte4.Index;
            }

            if (byte.TryParse(dgv[e.ColumnIndex, e.RowIndex].Value.ToString(), out cmdSize))
            {
                switch (cmdSize)
                {
                    case 1:
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte1Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte2Index, e.RowIndex], true, true);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte3Index, e.RowIndex], true, true);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte4Index, e.RowIndex], true, true);
                        break;
                    case 2:
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte1Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte2Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte3Index, e.RowIndex], true, true);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte4Index, e.RowIndex], true, true);
                        break;
                    case 3:
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte1Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte2Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte3Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte4Index, e.RowIndex], true, true);
                        break;
                    case 4:
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte1Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte2Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte3Index, e.RowIndex], false);
                        CyParameters.SetCellReadOnlyState(dgv[columnCmdByte4Index, e.RowIndex], false);
                        break;
                    default:
                        break;
                }
            }
        }

        private void InitializeDataGridView(DataGridView dgv)
        {
            dgv.EditMode = DataGridViewEditMode.EditOnEnter;
            dgv.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            dgv.AllowUserToResizeRows = false;
            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dgv.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;
            foreach (DataGridViewColumn item in dgv.Columns)
            {
                item.SortMode = DataGridViewColumnSortMode.NotSortable; // prevent data grid from sorting
            }
        }
        #endregion

        #region Validation
        private void CheckAPINameDuplicates()
        {
            for (int i = 0; i < dgvCustomCmds.RowCount; i++)
            {
                if (dgvCustomCmds[colCustApiName.Index, i].ErrorText == Resources.APINameDuplicate)
                {
                    dgvCustomCmds[colCustApiName.Index, i].ErrorText = string.Empty;
                }
            }

            // Mark items with duplicated names
            for (int i = 0; i < m_params.CustomCommands.Count; i++)
            {
                for (int j = 0; j < m_params.CustomCommands.Count; j++)
                {
                    if (i != j)
                    {
                        if ((string.IsNullOrEmpty(m_params.CustomCommands[i].ApiName) == false) &&
                            (m_params.CustomCommands[i].ApiName.Trim().ToLower() ==
                             m_params.CustomCommands[j].ApiName.Trim().ToLower()))
                        {
                            if (dgvCustomCmds[colCustApiName.Index, i].ErrorText == string.Empty)
                                dgvCustomCmds[colCustApiName.Index, i].ErrorText = Resources.APINameDuplicate;
                            if (dgvCustomCmds[colCustApiName.Index, j].ErrorText == string.Empty)
                                dgvCustomCmds[colCustApiName.Index, j].ErrorText = Resources.APINameDuplicate;
                        }
                    }
                }
            }
        }

        private bool RangeCheck(object sender, DataGridViewCellEventArgs e)
        {
            DataGridView dgv = (DataGridView)sender;
            if (dgv[e.ColumnIndex, e.RowIndex].ReadOnly || dgv.Enabled == false) return true;

            UInt16? currCellValue = null;
            CyCommandRow cmdRow;
            bool isHex = true;

            int min;
            int max;
            int columnCmdSizeIndex = -1;
            int columnDataSizeIndex = -1;
            int columnCmdByte1Index = -1;
            int columnCmdByte2Index = -1;
            int columnCmdByte3Index = -1;
            int columnCmdByte4Index = -1;

            if (dgv == dgvRequiredCmds)
            {
                columnCmdSizeIndex = colReqCmdSize.Index;
                columnDataSizeIndex = colReqDataSize.Index;
                columnCmdByte1Index = colReqCmdByte1.Index;
                columnCmdByte2Index = colReqCmdByte2.Index;
                columnCmdByte3Index = colReqCmdByte3.Index;
                columnCmdByte4Index = colReqCmdByte4.Index;
                cmdRow = m_params.RequiredCommands[e.RowIndex];
            }
            else
            {
                columnCmdSizeIndex = colCustCmdSize.Index;
                columnDataSizeIndex = colCustDataSize.Index;
                columnCmdByte1Index = colCustCmdByte1.Index;
                columnCmdByte2Index = colCustCmdByte2.Index;
                columnCmdByte3Index = colCustCmdByte3.Index;
                columnCmdByte4Index = colCustCmdByte4.Index;
                cmdRow = m_params.CustomCommands[e.RowIndex];
            }

            if (e.ColumnIndex == columnDataSizeIndex)
            {
                currCellValue = cmdRow.DataSize;
                isHex = false;
            }
            else if (e.ColumnIndex == columnCmdSizeIndex)
            {
                if (dgv[columnDataSizeIndex, e.RowIndex].Value != null)
                {
                    DataGridViewCellEventArgs dataSizeCellEvent = new DataGridViewCellEventArgs(
                                                                                 columnDataSizeIndex, e.RowIndex);
                    RangeCheck(sender, dataSizeCellEvent);
                }
                return true;
            }
            else if (e.ColumnIndex == columnCmdByte1Index)
            {
                currCellValue = cmdRow.CmdByte1;
            }
            else if (e.ColumnIndex == columnCmdByte2Index)
            {
                currCellValue = cmdRow.CmdByte2;
            }
            else if (e.ColumnIndex == columnCmdByte3Index)
            {
                currCellValue = cmdRow.CmdByte3;
            }
            else if (e.ColumnIndex == columnCmdByte4Index)
            {
                currCellValue = cmdRow.CmdByte4;
            }
            else
            {
                return true;
            }

            // Define range of cells
            if (e.ColumnIndex == columnDataSizeIndex || e.ColumnIndex == columnCmdSizeIndex)
            {
                // Range for DataSize
                min = CyParamRanges.DATA_SIZE_MIN;
                max = (cmdRow.CmdSize.HasValue) ?
                          (CyParamRanges.DATA_SIZE_MAX + 1 - cmdRow.CmdSize.Value) : CyParamRanges.DATA_SIZE_MAX;
            }
            else
            {
                // Range for Command Bytes
                min = CyParamRanges.DATA_SIZE_MIN;
                max = CyParamRanges.DATA_SIZE_MAX;
            }

            // If it is one of the columns that have to be checked than highlight or hide error provider
            if ((currCellValue.HasValue == false) || (currCellValue < min) || (currCellValue > max))
            {
                if (isHex)
                {
                    dgv[e.ColumnIndex, e.RowIndex].ErrorText =
                                                     string.Format(Resources.ValueOutOfRange,
                                                     CyParameters.ConvertDecToHex((byte)min),
                                                     CyParameters.ConvertDecToHex((byte)max));
                }
                else
                {
                    dgv[e.ColumnIndex, e.RowIndex].ErrorText =
                                                     string.Format(Resources.ValueOutOfRange, min, max);
                }
                return false;
            }
            else
            {
                dgv[e.ColumnIndex, e.RowIndex].ErrorText = String.Empty;
                return true;
            }
        }
        #endregion

        #region Other event handlers
        private void chbCommandPattern_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode == false) return;
            if (chbCommandPattern.Checked)
            {
                m_params.RequiredCommands.Insert(0, CyParameters.GetWritingDataCmdPattern());
                bool prevGEM = m_params.GlobalEditMode;
                m_params.GlobalEditMode = false;
                dgvRequiredCmds.Rows.Insert(0, new object[dgvRequiredCmds.ColumnCount]);
                UpdateRequiredUIFromTable(0);
                m_params.GlobalEditMode = prevGEM;
                m_params.SetRequiredCommands();
            }
            else
            {
                m_params.RequiredCommands.RemoveAt(0);
                dgvRequiredCmds.Rows.RemoveAt(0);
                m_params.SetRequiredCommands();
            }
            m_params.UseCmdPattern = chbCommandPattern.Checked;
        }

        private void CyCustomCommandsTab_VisibleChanged(object sender, EventArgs e)
        {
            UpdateRequiredUIFromTable();
            switch (m_params.CommandFormat)
            {
                case CyECommandFormat.Custom:
                    gbRequiredCommands.Enabled = true;
                    dgvRequiredCmds.ForeColor = SystemColors.ControlText;
                    dgvRequiredCmds.ColumnHeadersDefaultCellStyle.ForeColor = SystemColors.WindowText;
                    dgvRequiredCmds.EnableHeadersVisualStyles = true;
                    chbCommandPattern.Enabled = true;
                    break;
                case CyECommandFormat.NxpPlusCustom:
                    gbRequiredCommands.Enabled = false;
                    dgvRequiredCmds.ReadOnly = false;
                    dgvRequiredCmds.ForeColor = Color.Gray;
                    dgvRequiredCmds.ColumnHeadersDefaultCellStyle.ForeColor = Color.Gray;
                    dgvRequiredCmds.EnableHeadersVisualStyles = false;
                    chbCommandPattern.Enabled = false;
                    break;
                default:
                    break;
            }

            chbCommandPattern.Checked = m_params.UseCmdPattern;
        }

        private void m_contextMenu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            m_contextMenu.Hide();
            if (MessageBox.Show(Resources.DeletePrompt, Resources.ComponentName, MessageBoxButtons.YesNo,
                            MessageBoxIcon.Warning) == DialogResult.Yes)
            {
                foreach (DataGridViewRow item in dgvCustomCmds.SelectedRows)
                {
                    if (item.IsNewRow == false)
                    {
                        m_params.CustomCommands.RemoveAt(item.Index);
                        dgvCustomCmds.Rows.Remove(item);
                        m_params.SetCustomCommands();
                        CheckAPINameDuplicates();
                    }
                }
            }
        }
        #endregion
    }
}
