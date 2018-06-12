/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace SMBusSlave_v5_20
{
    public partial class CyCustomCmdsTab : CyTabWrapper
    {
        #region Private variables declaration
        private ContextMenuStrip m_contextMenu;
        private byte? m_currentCmdCode = null;
        private bool m_showReservedBootloaderRows;
        // This variable contains Type field value before it was changed. 
        // This is necessary to dicide either to overwrite Size field with default value or not.
        private object m_previousType = null;
        private DataGridViewRow m_pageCmdRowRef;
        private DataGridViewRow m_queryCmdRowRef;
        #endregion

        #region CyTabControlWrapper members
        public override string TabName
        {
            get { return "Custom Commands"; }
        }
        #endregion

        #region Constructor(s)
        public CyCustomCmdsTab(CyParameters parameters, CyApplicationType_v1 appType)
            : base(parameters)
        {
            m_params.CustomCmdsTab = this;
            m_showReservedBootloaderRows = (appType == CyApplicationType_v1.Bootloader);
            InitializeComponent();

            // Initialize wrapper objects
            m_wrapperDataGridView = dgv;
            m_wrapperDataGridKeyColumIndex = colReference.Index;
            m_wrapperToolStrip = cyToolStrip1;

            // Initialize toolstrip            
            cyToolStrip1.m_params = parameters;
            cyToolStrip1.m_dgv = dgv;

            CyParameters.CustomTableHeader_v2 = CyParameters.GetColNames(dgv);

            // Fill grid comboboxes
            colType.Items.Clear();
            colType.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyECmdType)));
            colReadConfig.Items.Clear();
            colReadConfig.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEReadWriteConfigType)));
            colWriteConfig.Items.Clear();
            colWriteConfig.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEReadWriteConfigType)));
            colFormat.Items.Clear();
            colFormat.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEFormatType)));

            // Initialize data grid view
            CyParameters.InitializeDataGrid(dgv);
            colCommandName.SortMode = DataGridViewColumnSortMode.Automatic;
            colCode.SortMode = DataGridViewColumnSortMode.Automatic;

            m_editableCols = new List<int>(new int[]
            {
                colEnable.Index,
                colCommandName.Index,
                colCode.Index,
                colType.Index,
                colFormat.Index,
                colSize.Index,
                colPaged.Index,
                colNumPages.Index,
                colReadConfig.Index,
                colWriteConfig.Index
            });

            dgv.CurrentCellDirtyStateChanged += delegate(object sender, EventArgs e)
            {
                if (dgv.CurrentCell != null)
                {
                    if (dgv.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell))
                        if (dgv.IsCurrentCellDirty)
                            dgv.CommitEdit(DataGridViewDataErrorContexts.Commit);

                    // Commit Type immediately after selecting
                    if (dgv.CurrentCell.GetType() == typeof(DataGridViewComboBoxCell) &&
                        dgv.CurrentCell.ColumnIndex == colType.Index)
                    {
                        if (dgv.IsCurrentCellDirty)
                        {
                            m_previousType = dgv.CurrentCell.Value;
                            dgv.CommitEdit(DataGridViewDataErrorContexts.Commit);
                        }
                    }
                }
                if (dgv.CurrentCell.ColumnIndex == colType.Index)
                {
                    UpdateTypeDependentCells(dgv.CurrentCell.RowIndex, m_previousType, dgv.CurrentCell.Value, true);
                }
            };
            dgv.CellValueChanged += new DataGridViewCellEventHandler(dataGridView_CellValueChanged);

            UpdateUIFromTable();
            ValidateAllTable();
            m_contextMenu = new ContextMenuStrip();
            m_contextMenu.Items.Add(Resources.ContextMenuDeleteItem);
            m_contextMenu.ItemClicked += new ToolStripItemClickedEventHandler(m_contextMenu_ItemClicked);
        }
        #endregion

        #region Restrict Size and Read/Write config controls
        private void UpdateTypeDependentCells(int rowIndex, object type)
        {
            UpdateTypeDependentCells(rowIndex, null, type, false);
        }

        private void UpdateTypeDependentCells(int rowIndex, object prevValue, object newValue, bool overwriteSize)
        {
            if (rowIndex >= dgv.Rows.Count) 
            {
                Debug.Fail("Invalid rowIndex");
                return;
            }

            CyCustomTableRow customTableRow = (CyCustomTableRow)dgv[colReference.Index, rowIndex].Value;

            if (customTableRow == null)  // for existing row only
            {
                Debug.Fail("Custom table row not set");
                return;
            }

            DataGridViewTextBoxCell sizeCell = (DataGridViewTextBoxCell)dgv.Rows[rowIndex].Cells[colSize.Index];
            DataGridViewComboBoxCell writeConfigCell =
                (DataGridViewComboBoxCell)dgv.Rows[rowIndex].Cells[colWriteConfig.Index];
            DataGridViewComboBoxCell readConfigCell =
                (DataGridViewComboBoxCell)dgv.Rows[rowIndex].Cells[colReadConfig.Index];

            CyECmdType prevType;
            if (prevValue != null)
                prevType = (CyECmdType)CyEnumConverter.GetEnumValue(prevValue, typeof(CyECmdType));
            else
                prevType = (CyECmdType)CyEnumConverter.GetEnumValue(newValue, typeof(CyECmdType));

            string autoItemText = CyEnumConverter.GetEnumValue(CyEReadWriteConfigType.Auto,
                typeof(CyEReadWriteConfigType)).ToString();
            string manualItemText = CyEnumConverter.GetEnumValue(CyEReadWriteConfigType.Manual,
                typeof(CyEReadWriteConfigType)).ToString();
            string noneItemText = CyEnumConverter.GetEnumValue(CyEReadWriteConfigType.None,
                typeof(CyEReadWriteConfigType)).ToString();

            Dictionary<CyEReadWriteConfigType, string> readWriteConfigTypeDict = 
                new Dictionary<CyEReadWriteConfigType, string>();
            readWriteConfigTypeDict.Add(CyEReadWriteConfigType.Auto, autoItemText);
            readWriteConfigTypeDict.Add(CyEReadWriteConfigType.Manual, manualItemText);
            readWriteConfigTypeDict.Add(CyEReadWriteConfigType.None, noneItemText);

            CyEReadWriteConfigType[] sendByteReadOptions = new CyEReadWriteConfigType[] 
            { CyEReadWriteConfigType.None };
            CyEReadWriteConfigType[] sendByteWriteOptions = new CyEReadWriteConfigType[] 
            { CyEReadWriteConfigType.Manual, CyEReadWriteConfigType.None };
            CyEReadWriteConfigType[] readWriteByteReadWriteOptions = new CyEReadWriteConfigType[] 
            { CyEReadWriteConfigType.Auto, CyEReadWriteConfigType.Manual, CyEReadWriteConfigType.None };
            CyEReadWriteConfigType[] processCallReadWriteOptions = new CyEReadWriteConfigType[]
            { CyEReadWriteConfigType.Manual, CyEReadWriteConfigType.None };
            CyEReadWriteConfigType[] blockProcessCallReadWriteOptions = new CyEReadWriteConfigType[] 
            { CyEReadWriteConfigType.Manual, CyEReadWriteConfigType.None };

            CyECmdType currentType = (CyECmdType)CyEnumConverter.GetEnumValue(newValue, typeof(CyECmdType));

            switch (currentType)
            {
                case CyECmdType.SendByte:
                    // Size
                    if (overwriteSize)
                        sizeCell.Value = CyParamRange.SEND_BYTE_SIZE;
                    CyParameters.SetCellReadOnlyState(sizeCell, true);

                    // Read/Write config
                    UpdateReadWriteComboCells(readConfigCell, sendByteReadOptions, readWriteConfigTypeDict);
                    UpdateReadWriteComboCells(writeConfigCell, sendByteWriteOptions, readWriteConfigTypeDict);
                    break;
                case CyECmdType.ReadWriteByte:
                case CyECmdType.ReadWriteWord:
                case CyECmdType.ReadWriteBlock:
                    // Size
                    if (currentType == CyECmdType.ReadWriteByte)
                    {
                        if (overwriteSize)
                            sizeCell.Value = CyParamRange.READ_WRITE_BYTE_SIZE;
                        CyParameters.SetCellReadOnlyState(sizeCell, true);
                    }
                    if (currentType == CyECmdType.ReadWriteWord)
                    {
                        if (overwriteSize)
                            sizeCell.Value = CyParamRange.READ_WRITE_WORD_SIZE;
                        CyParameters.SetCellReadOnlyState(sizeCell, true);
                    }
                    if (currentType == CyECmdType.ReadWriteBlock)
                    {
                        CyParameters.SetCellReadOnlyState(sizeCell, false);
                    }

                    // Read/Write config
                    UpdateReadWriteComboCells(readConfigCell, readWriteByteReadWriteOptions, readWriteConfigTypeDict);
                    UpdateReadWriteComboCells(writeConfigCell, readWriteByteReadWriteOptions, readWriteConfigTypeDict);
                    break;
                case CyECmdType.ProcessCall:
                    // Size
                    if (overwriteSize)
                        sizeCell.Value = CyParamRange.READ_WRITE_WORD_SIZE;
                    CyParameters.SetCellReadOnlyState(sizeCell, true);

                    // Read/Write config
                    UpdateReadWriteComboCells(readConfigCell, processCallReadWriteOptions, readWriteConfigTypeDict);
                    UpdateReadWriteComboCells(writeConfigCell, processCallReadWriteOptions, readWriteConfigTypeDict);
                    break;
                case CyECmdType.BlockProcessCall:
                    // Size
                    if (overwriteSize)
                    {
                        if (prevType == CyECmdType.SendByte || prevType == CyECmdType.ReadWriteByte ||
                            prevType == CyECmdType.ReadWriteWord || prevType == CyECmdType.ProcessCall)
                        {
                            sizeCell.Value = CyParamRange.BLOCK_PROCESS_CALL_SIZE;
                        }
                    }
                    CyParameters.SetCellReadOnlyState(sizeCell, false);

                    // Read/Write config
                    UpdateReadWriteComboCells(readConfigCell, blockProcessCallReadWriteOptions, readWriteConfigTypeDict);
                    UpdateReadWriteComboCells(writeConfigCell, blockProcessCallReadWriteOptions, 
                        readWriteConfigTypeDict);
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }


            foreach (DataGridViewColumn column in dgv.Columns)
            {
                // Read/Write config for PAGE command should not contain None item
                if ((column.Index == colReadConfig.Index || column.Index == colWriteConfig.Index) &&
                    customTableRow.m_name == CyCustomTable.PAGE)
                {
                    DataGridViewComboBoxCell configCell = (DataGridViewComboBoxCell)dgv.Rows[rowIndex].Cells[
                        column.Index];

                    // PAGE command belongs to GROUP6
                    configCell.Items.Clear();
                    configCell.Items.Add(CyEnumConverter.GetEnumDesc(CyEReadWriteConfigType.Auto));
                    configCell.Items.Add(CyEnumConverter.GetEnumDesc(CyEReadWriteConfigType.Manual));
                }
            }

            // QUERY command is read-only and Read config should contain Auto item
            if (customTableRow.m_name == CyCustomTable.QUERY)
            {
                readConfigCell.Items.Clear();
                readConfigCell.Items.Add(CyEnumConverter.GetEnumDesc(customTableRow.m_readConfig));
                readConfigCell.Value = CyEnumConverter.GetEnumDesc(customTableRow.m_readConfig);
            }
        }

        private void UpdateReadWriteComboCells(DataGridViewComboBoxCell cell, CyEReadWriteConfigType[] items, 
            Dictionary<CyEReadWriteConfigType, string> descriptions)
        {
            bool itemsCorrect = cell.Items.Count == items.Length;
            for (int i = 0; i < items.Length; i++)
            {
                itemsCorrect &= cell.Items.Contains(items[i]);
            }

            if (itemsCorrect == false)
            {
                cell.Items.Clear();
                for (int i = 0; i < items.Length; i++)
                {
                    cell.Items.Add(descriptions[items[i]]);
                }
                if (cell.Items.Contains(cell.Value) == false)
                    cell.Value = descriptions[items[0]];
            }
        }
        #endregion

        #region Update table/datagrid
        public override void UpdateUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            dgv.Rows.Clear();

            for (int row = 0; row < m_params.CustomTable.Count; row++)
            {
                object[] newRow = new object[dgv.ColumnCount];
                dgv.Rows.Add(newRow);

                UpdateUIFromTable(row);
            }
            dgv.AllowUserToAddRows = true;
            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateTableFromUI()
        {
            for (int row = 0; row < m_params.CustomTable.Count; row++)
            {
                UpdateTableRowFromUI(row);
            }
        }

        public override void UpdateUIFromTable(int row)
        {
            dgv[colReference.Index, row].Value = m_params.CustomTable[row];
            dgv[colEnable.Index, row].Value = m_params.CustomTable[row].m_enable;
            dgv[colCode.Index, row].Value = CyParameters.NullableByteToHex(m_params.CustomTable[row].m_code);
            dgv[colCommandName.Index, row].Value = m_params.CustomTable[row].m_name;
            dgv[colType.Index, row].Value = CyEnumConverter.GetEnumDesc(m_params.CustomTable[row].m_type);
            dgv[colSize.Index, row].Value = m_params.CustomTable[row].m_size;
            dgv[colFormat.Index, row].Value = CyEnumConverter.GetEnumDesc(m_params.CustomTable[row].m_format);
            dgv[colPaged.Index, row].Value = m_params.CustomTable[row].m_paged;
            dgv[colNumPages.Index, row].Value = m_params.CustomTable[row].m_numPages;
            dgv[colReadConfig.Index, row].Value = CyEnumConverter.GetEnumDesc(
                m_params.CustomTable[row].m_readConfig);
            dgv[colWriteConfig.Index, row].Value = CyEnumConverter.GetEnumDesc(
                m_params.CustomTable[row].m_writeConfig);

            if (m_params.CustomTable[row].m_specific && (m_params.CustomTable[row].m_name == CyCustomTable.PAGE))
                m_pageCmdRowRef = dgv.Rows[row];
            if (m_params.CustomTable[row].m_specific && (m_params.CustomTable[row].m_name == CyCustomTable.QUERY))
                m_queryCmdRowRef = dgv.Rows[row];

            // Remove restricted items from Read and Write configuration combo boxes
            UpdateTypeDependentCells(row, dgv[colType.Index, row].Value);

            // Gray out NumPages if commands is not paged
            CyParameters.SetCellReadOnlyState(dgv[colNumPages.Index, row], m_params.CustomTable[row].m_paged == false);

            // All cells except code should be disabled for specific commands
            if (m_params.CustomTable[row].m_specific)
            {
                foreach (DataGridViewColumn column in dgv.Columns)
                {
                    if (column.Index != colCode.Index)
                    {
                        // Read/Write config columns for PAGE command should be editable
                        if (((column.Index == colReadConfig.Index || column.Index == colWriteConfig.Index) &&
                            m_params.CustomTable[row].m_name == CyCustomTable.PAGE) ||
                            // Enable column for BOOTLOADER commands should be editable in Bootloadable project
                            // or when projects is bootloader but BOOTLOADER commands are disabled, so user could
                            // enable the commands
                            (column.Index == colEnable.Index &&
                            m_params.CustomTable[row].m_specific &&
                            CyCustomTable.IsCmdBootloader(m_params.CustomTable[row].m_name) &&
                            m_params.m_isBootloader &&
                            (m_params.InstQuery.DesignQuery.ApplicationType == CyApplicationType_v1.Bootloadable ||
                            m_params.CustomTable[row].m_enable == false)))
                        {
                            CyParameters.SetCellReadOnlyState(dgv, column.Index, row, false);
                        }
                        else
                        {
                            CyParameters.SetCellReadOnlyState(dgv, column.Index, row, true);
                        }
                    }
                }
            }
        }

        public override void UpdateTableRowFromUI(int row)
        {
            int tableIndex = m_params.GetCustomTableIndexByReference((CyCustomTableRow)dgv[colReference.Index,
                    row].Value);
          
            if (tableIndex < 0)
            {
                m_params.CustomTable.Add(new CyCustomTableRow());
                tableIndex = m_params.CustomTable.Count - 1;

                // Connect datagrid to table object
                bool prevGEM = m_params.GlobalEditMode;
                m_params.GlobalEditMode = false;
                dgv[colReference.Index, row].Value = m_params.CustomTable[tableIndex];
                m_params.GlobalEditMode = prevGEM;
            }

            CyCustomTableRow customTableRow = m_params.CustomTable[tableIndex];
            DataGridViewRow dgvTableRow = dgv.Rows[row];

            customTableRow.m_enable = CyParameters.CellToBool(dgvTableRow.Cells[colEnable.Index].Value);
            customTableRow.m_name = CyParameters.CellToString(dgvTableRow.Cells[colCommandName.Index].Value);
            customTableRow.m_code = CyParameters.ParseNullableHexByte(dgvTableRow.Cells[colCode.Index].Value);
            customTableRow.m_type = (CyECmdType)CyEnumConverter.GetEnumValue(
                dgvTableRow.Cells[colType.Index].Value, typeof(CyECmdType));
            customTableRow.m_format = (CyEFormatType)CyEnumConverter.GetEnumValue(
                dgvTableRow.Cells[colFormat.Index].Value, typeof(CyEFormatType));
            customTableRow.m_size = CyParameters.ParseNullableByte(dgvTableRow.Cells[colSize.Index].Value);
            customTableRow.m_paged = CyParameters.CellToBool(dgvTableRow.Cells[colPaged.Index].Value);
            customTableRow.m_numPages = CyParameters.ParseNullableByte(dgvTableRow.Cells[colNumPages.Index].Value);
            customTableRow.m_readConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                dgvTableRow.Cells[colReadConfig.Index].Value, typeof(CyEReadWriteConfigType));
            customTableRow.m_writeConfig = (CyEReadWriteConfigType)CyEnumConverter.GetEnumValue(
                dgvTableRow.Cells[colWriteConfig.Index].Value, typeof(CyEReadWriteConfigType));
        }

        public void AddPageCommandRow()
        {
            m_params.CustomTable.Insert(CyCustomTable.PAGE_INDEX, CyCustomTable.GetDefaultPageRow());
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            dgv.Rows.Insert(0, new object[dgv.ColumnCount]);
            UpdateUIFromTable(0);
            m_params.GlobalEditMode = prevGEM;
            m_params.SetCustomTable();
        }

        public void RemovePageCommandRow()
        {
            if (m_pageCmdRowRef != null && m_pageCmdRowRef.Index >= 0)
            {
                CyCustomTableRow dataRow = (CyCustomTableRow)dgv[colReference.Index, m_pageCmdRowRef.Index].Value;
                m_params.CustomTable.Remove(dataRow);
                dgv.Rows.Remove(m_pageCmdRowRef);
                m_params.SetCustomTable();
            }
        }

        public bool IsCommandRowPresent(string commandName, int maxIndexLocation)
        {
            maxIndexLocation = Math.Min(maxIndexLocation, m_params.CustomTable.Count - 1);
            for (int i = 0; i <= maxIndexLocation; i++)
            {
                if (m_params.CustomTable[i].m_name == commandName)
                    return true;
            }
            return false;
        }

        public void AddQueryCommandRow()
        {
            int whereToInsert = ((m_params.PageVisible &&
                (dgv[colCommandName.Index, 0].Value.ToString() == CyCustomTable.PAGE)) ? CyCustomTable.QUERY_INDEX : 
                CyCustomTable.QUERY_INDEX - 1);
            m_params.CustomTable.Insert(whereToInsert, CyCustomTable.GetDefaultQueryRow());
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            dgv.Rows.Insert(whereToInsert, new object[dgv.ColumnCount]);
            UpdateUIFromTable(whereToInsert);
            m_params.GlobalEditMode = prevGEM;
            m_params.SetCustomTable();
        }

        public void RemoveQueryCommandRow()
        {
            if (m_queryCmdRowRef != null && m_queryCmdRowRef.Index >= 0)
            {
                CyCustomTableRow dataRow = (CyCustomTableRow)dgv[colReference.Index, m_queryCmdRowRef.Index].Value;
                m_params.CustomTable.Remove(dataRow);
                dgv.Rows.Remove(m_queryCmdRowRef);
                m_params.SetCustomTable();
            }
        }
        #endregion

        #region Event handlers
        private void dataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                // Validate Command Name cell
                if (e.ColumnIndex == colCommandName.Index)
                {
                    // Input name to upper case
                    string val = CyParameters.CellToString(dgv[e.ColumnIndex, e.RowIndex].Value).ToUpper();
                    if (CyParameters.CellToString(dgv[e.ColumnIndex, e.RowIndex].Value) != val)
                    {
                        dgv[e.ColumnIndex, e.RowIndex].Value = val;
                        return;
                    }
                    // Check name syntax
                    NameSyntaxCheck(e.RowIndex);
                }
                if (e.ColumnIndex == colPaged.Index)
                {
                    bool isReadOnly = CyParameters.CellToBool(dgv[e.ColumnIndex, e.RowIndex].Value) == false;
                    CyParameters.SetCellReadOnlyState(dgv[colNumPages.Index, e.RowIndex], isReadOnly);
                    if (isReadOnly)
                        dgv[colNumPages.Index, e.RowIndex].ErrorText = String.Empty;
                }
                UpdateTableRowFromUI(e.RowIndex);
                m_params.SetCustomTable();
                ValidateRow(e.RowIndex);
                if (e.ColumnIndex == colCommandName.Index)
                {
                    ValidateNames();
                }
                if ((e.ColumnIndex == colCode.Index) || (e.ColumnIndex == colEnable.Index))
                {
                    ValidateCodes();
                    m_params.PmBusCmdsTab.ValidateCodes(); // update error providers on PM Bus tab
                }
                if (e.ColumnIndex == colEnable.Index)
                {
                    // Gray out Enable column if it is enabled in not Bootloadable project
                    CyCustomTableRow currentRow = (CyCustomTableRow)dgv[colReference.Index, e.RowIndex].Value;
                    if (currentRow != null)
                    {
                        if (m_params.InstQuery.DesignQuery.ApplicationType != CyApplicationType_v1.Bootloadable &&
                            currentRow.m_enable && currentRow.m_specific &&
                            CyCustomTable.IsCmdBootloader(currentRow.m_name))
                        {
                            CyParameters.SetCellReadOnlyState(dgv, e.ColumnIndex, e.RowIndex, true);
                        }
                    }

                    NameSyntaxCheck(e.RowIndex);
                    ValidateNames();
                }
            }
        }

        private void dgv_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (e.Value != null)
            {
                if (e.ColumnIndex == colCode.Index)
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

        private void dgv_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (dgv.CurrentRow.Cells[colType.Index].Value == null)
                {
                    bool prevGEM = m_params.GlobalEditMode;
                    m_params.GlobalEditMode = false;

                    dgv.CurrentRow.Cells[colType.Index].Value = CyEnumConverter.GetEnumDesc(CyECmdType.ReadWriteByte);
                    if (dgv.CurrentCell == dgv.CurrentRow.Cells[colSize.Index])
                    {
                        dgv.CurrentRow.Cells[colType.Index].Value = CyEnumConverter.GetEnumDesc(
                                                                                    CyECmdType.ReadWriteBlock);
                    }
                    else
                    {
                        dgv.CurrentRow.Cells[colSize.Index].Value = 1;
                    }
                    dgv.CurrentRow.Cells[colFormat.Index].Value = CyEnumConverter.GetEnumDesc(
                        CyEFormatType.NonNumeric);
                    if (dgv.CurrentCell == dgv.CurrentRow.Cells[colNumPages.Index])
                    {
                        dgv.CurrentRow.Cells[colPaged.Index].Value = true;
                    }
                    else
                    {
                        dgv.CurrentRow.Cells[colNumPages.Index].Value = m_params.PagedCommands;
                    }
                    dgv.CurrentRow.Cells[colReadConfig.Index].Value = CyEnumConverter.GetEnumDesc(
                        CyEReadWriteConfigType.Manual);
                    dgv.CurrentRow.Cells[colWriteConfig.Index].Value = CyEnumConverter.GetEnumDesc(
                        CyEReadWriteConfigType.Manual);

                    m_params.GlobalEditMode = prevGEM;
                }
                UpdateTableRowFromUI(dgv.CurrentRow.Index);
                UpdateTypeDependentCells(dgv.CurrentRow.Index, dgv[colType.Index, dgv.CurrentRow.Index].Value);
                // Gray out NumPages if commands are not paged
                CyParameters.SetCellReadOnlyState(dgv[colNumPages.Index, dgv.CurrentRow.Index],
                                                 (m_params.CustomTable[dgv.CurrentRow.Index].m_paged == false));
            }
        }

        private void m_contextMenu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            m_contextMenu.Hide();
            if (MessageBox.Show(Resources.DeletePrompt, Resources.SMBusSlaveName, MessageBoxButtons.YesNo,
                            MessageBoxIcon.Warning) == DialogResult.Yes)
            {
                foreach (DataGridViewRow item in dgv.SelectedRows)
                {
                    if (item.IsNewRow == false)
                    {
                        CyCustomTableRow dataRow = (CyCustomTableRow)dgv[colReference.Index, item.Index].Value;
                        // Do not removed SPECIFIC (readonly) rows
                        if (dgv[colCommandName.Index, item.Index].ReadOnly == false)
                        {
                            m_params.CustomTable.Remove(dataRow);
                            dgv.Rows.Remove(item);
                            m_params.SetCustomTable();
                            m_params.CustomCmdsTab.ValidateCodes();
                            m_params.PmBusCmdsTab.ValidateCodes();
                            m_params.CustomCmdsTab.ValidateNames();
                        }
                    }
                }
            }
        }

        private void dgv_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            if (e.ColumnIndex == colCode.Index)
            {
                m_currentCmdCode = CyParameters.ParseNullableHexByte(dgv[e.ColumnIndex, e.RowIndex].Value);
            }
        }

        private void dgv_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                DataGridView.HitTestInfo ht = dgv.HitTest(e.X, e.Y);
                if (ht.RowIndex < dgv.RowCount - 1) // last row is "new row" and cannot be deleted
                    if (ht.Type == DataGridViewHitTestType.RowHeader && dgv.SelectedRows.Count > 0)
                    {
                        m_contextMenu.Show(MousePosition);
                    }
            }
        }

        private void dgv_RowHeaderMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex < dgv.RowCount - 1) // last row is "new row" and cannot be deleted
                m_contextMenu_ItemClicked(sender, new ToolStripItemClickedEventArgs(m_contextMenu.Items[0]));
        }

        private void dgv_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(sender as DataGridView);
        }

        public void ShowHideImportExportAllFeature(bool show)
        {
            m_wrapperToolStrip.ShowHideImportExportAllFeature(show);
        }
        #endregion

        #region Validation
        private bool NameSyntaxCheck(int rowIndex)
        {
            bool result = true;
            string message = string.Empty;
            string inputName = string.Empty;

            CyCustomTableRow currentRow = (CyCustomTableRow)dgv[colReference.Index, rowIndex].Value;
            if ((dgv[colCommandName.Index, rowIndex].Value != null &&
                 currentRow != null && currentRow.m_specific == false) &&
                // Command is not specific and enabled
                ((currentRow.m_enable == true) ||
                // Command is not specific and disabled but has a name like a specific
                (currentRow.m_enable == false &&
                 CyCustomTable.IsCmdSpecific(currentRow.m_name))))
            {
                inputName = CyParameters.CellToString(dgv[colCommandName.Index, rowIndex].Value);
                if (CyCustomTable.IsCmdSpecific(inputName.Trim()))
                {
                    result = false;
                    message = string.Format(Resources.CmdNameReserved, inputName.Trim());
                }
                else if (inputName.Length > 0 && Char.IsDigit(inputName[0]))
                {
                    result = false;
                    message = Resources.CmdNameInvalid;
                }
                else if (System.Text.RegularExpressions.Regex.Match(
                    inputName, @"([A-Za-z0-9_]*)").Length != inputName.Length)
                {
                    result = false;
                    message = Resources.CmdNameInvalid;
                }
                else
                {
                    result = true;
                }
            }
            dgv[colCommandName.Index, rowIndex].ErrorText = result ? string.Empty : message;
            return result;
        }

        public override void ValidateNames()
        {
            for (int i = 0; i < dgv.RowCount; i++)
            {
                if (dgv[colCommandName.Index, i].ErrorText != string.Empty &&
                    dgv[colCommandName.Index, i].ErrorText != Resources.CmdNameInvalid)
                {
                    dgv[colCommandName.Index, i].ErrorText = string.Empty;
                }
            }

            // Mark items with duplicated names
            for (int i = 0; i < m_params.CustomTable.Count; i++)
            {
                for (int j = 0; j < m_params.CustomTable.Count; j++)
                {
                    if (i != j)
                    {
                        if ((string.IsNullOrEmpty(m_params.CustomTable[i].m_name) == false) &&
                            (m_params.CustomTable[i].m_name == m_params.CustomTable[j].m_name) &&
                            (m_params.CustomTable[i].m_enable && m_params.CustomTable[j].m_enable) &&
                            (m_params.CustomTable[i].m_specific == false &&
                             m_params.CustomTable[j].m_specific == false))
                        {
                            for (int k = 0; k < dgv.RowCount; k++)
                            {
                                if ((dgv[colReference.Index, k].Value == m_params.CustomTable[i]) ||
                                    (dgv[colReference.Index, k].Value == m_params.CustomTable[j]))
                                {
                                    if (dgv[colCommandName.Index, k].ErrorText == string.Empty)
                                        dgv[colCommandName.Index, k].ErrorText = Resources.CmdNameDuplicate;
                                }
                            }
                        }
                    }
                }

                // Validate reserved names
                if (m_params.CustomTable[i].m_specific == false &&
                    CyParameters.ReservedCmdNames.Contains(m_params.CustomTable[i].m_name.Trim()))
                {
                    for (int k = 0; k < dgv.RowCount; k++)
                    {
                        if (dgv[colReference.Index, k].Value == m_params.CustomTable[i])
                        {
                            dgv[colCommandName.Index, k].ErrorText = string.Format(Resources.CmdNameReserved,
                                m_params.CustomTable[i].m_name.Trim());
                        }
                    }
                }
            }
        }

        protected override bool RangeCheck(int rowIndex, int colIndex)
        {
            if (m_editableCols.Contains(colIndex) == false) return true; // do not apply below code to readonly columns
            if (colIndex == colCommandName.Index) return true; // Command Name column has own check rules

            double min = 0;
            double max = 0;
            string message = String.Empty;
            byte? currCellValue = null;
            bool displayHex = false;
            CyCustomTableRow customTableRow = (CyCustomTableRow)dgv[colReference.Index, rowIndex].Value;

            if (rowIndex < m_params.CustomTable.Count)
            {
                if (colIndex == colCode.Index)
                {
                    min = CyParamRange.CMD_CODE_MIN;
                    max = CyParamRange.CMD_CODE_MAX;
                    message = Resources.CodeOutOfRange;
                    currCellValue = customTableRow.m_code;
                    displayHex = true;
                }
                if (colIndex == colSize.Index)
                {
                    min = byte.MinValue;
                    max = CyParamRange.CMD_SIZE_MAX;
                    message = Resources.SizeOutOfRange;
                    currCellValue = customTableRow.m_size;
                }
                if (colIndex == colNumPages.Index)
                {
                    min = CyParamRange.PAGED_CMDS_MIN;
                    max = m_params.PagedCommands;
                    message = Resources.NumberOfPagesOutOfRange;
                    currCellValue = customTableRow.m_numPages;
                }

                if (m_editableCols.Contains(colIndex))
                {
                    if (dgv[colIndex, rowIndex].ReadOnly == false && customTableRow.m_enable)
                    {
                        message = CyParameters.IsValueInRange(currCellValue, dgv[colIndex, rowIndex].Value, min, max,
                            message, displayHex);
                    }
                    else
                    {
                        message = String.Empty;
                    }
                }
                dgv[colIndex, rowIndex].ErrorText = message;
            }
            return String.IsNullOrEmpty(message);
        }

        protected override bool SanityCheck(int rowIndex)
        {
            // Check Enable column
            string errorMessage = String.Empty;
            CyCustomTableRow currentRow = (CyCustomTableRow)dgv[colReference.Index, rowIndex].Value;
            if (currentRow != null)
            {
                if (m_params.InstQuery.DesignQuery.ApplicationType != CyApplicationType_v1.Bootloadable &&
                    currentRow.m_enable == false && currentRow.m_specific &&
                    CyCustomTable.IsCmdBootloader(currentRow.m_name))
                {
                    errorMessage = Resources.BootloadCommandNotEnabled;
                }
            }
            dgv[colEnable.Index, rowIndex].ErrorText = errorMessage;
            return String.IsNullOrEmpty(errorMessage);
        }

        public override void ValidateCodes()
        {
            // Reset UI error providers
            for (int i = 0; i < dgv.RowCount; i++)
            {
                if (dgv[colCode.Index, i].ErrorText == Resources.CmdCodeUsed)
                    dgv[colCode.Index, i].ErrorText = string.Empty;
            }

            // Mark items with duplicated codes
            for (int i = 0; i < m_params.CustomTable.Count; i++)
            {
                for (int j = 0; j < m_params.CustomTable.Count; j++)
                {
                    if (i != j)
                    {
                        if ((m_params.CustomTable[i].m_code != null))
                        {
                            if ((m_params.CustomTable[i].m_code == m_params.CustomTable[j].m_code) &&
                                m_params.CustomTable[i].m_enable && m_params.CustomTable[j].m_enable)
                            {
                                for (int k = 0; k < dgv.RowCount; k++)
                                {
                                    if ((dgv[colReference.Index, k].Value == m_params.CustomTable[i]) ||
                                        (dgv[colReference.Index, k].Value == m_params.CustomTable[j]))
                                    {
                                        if (dgv[colCode.Index, k].ErrorText == string.Empty)
                                            dgv[colCode.Index, k].ErrorText = Resources.CmdCodeUsed;
                                    }
                                }
                            }
                        }
                    }
                }

                // Validate reserved codes
                if (m_params.CustomTable[i].m_code.HasValue)
                {
                    if (CyParameters.ReservedCmdCodes.Contains(m_params.CustomTable[i].m_code.Value))
                    {
                        for (int k = 0; k < dgv.RowCount; k++)
                        {
                            if (dgv[colReference.Index, k].Value == m_params.CustomTable[i])
                            {
                                dgv[colCode.Index, k].ErrorText = string.Format(Resources.CmdCodeReserved,
                                    CyParameters.CellConvertHex(m_params.CustomTable[i].m_code.Value));
                            }
                        }
                    }
                }
            }

            // Compare to PM Bus table
            if (m_params.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_params.PmBusTable.Count; i++)
                {
                    for (int j = 0; j < m_params.CustomTable.Count; j++)
                    {
                        if ((m_params.PmBusTable[i].m_code == m_params.CustomTable[j].m_code) &&
                            (m_params.PmBusTable[i].m_enable && m_params.CustomTable[j].m_enable))
                        {
                            for (int k = 0; k < dgv.RowCount; k++)
                            {
                                if (dgv[colReference.Index, k].Value == m_params.CustomTable[j])
                                {
                                    dgv[colCode.Index, k].ErrorText = Resources.CmdCodeUsed;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        #endregion

        #region Handling specific commands
        public void SetPageVisibility()
        {
            if (m_params.GlobalEditMode)
            {
                if (m_params.PageVisible)
                {
                    if (m_params.CustomCmdsTab.IsCommandRowPresent(CyCustomTable.PAGE, CyCustomTable.PAGE_INDEX) == false)
                        m_params.CustomCmdsTab.AddPageCommandRow();
                }
                else
                {
                    if (m_params.CustomCmdsTab.IsCommandRowPresent(CyCustomTable.PAGE, CyCustomTable.PAGE_INDEX))
                        m_params.CustomCmdsTab.RemovePageCommandRow();
                }

                m_params.CustomCmdsTab.ValidateCodes();
                m_params.CustomCmdsTab.ValidateNames();
            }
        }

        public void SetQueryVisibility()
        {
            if (m_params.GlobalEditMode)
            {
                if (m_params.QueryVisible)
                {
                    if (m_params.CustomCmdsTab.IsCommandRowPresent(CyCustomTable.QUERY, CyCustomTable.QUERY_INDEX) == false)
                        m_params.CustomCmdsTab.AddQueryCommandRow();
                }
                else
                {
                    if (m_params.CustomCmdsTab.IsCommandRowPresent(CyCustomTable.QUERY, CyCustomTable.QUERY_INDEX))
                        m_params.CustomCmdsTab.RemoveQueryCommandRow();
                }

                m_params.CustomCmdsTab.ValidateCodes();
                m_params.CustomCmdsTab.ValidateNames();
            }
        }
        #endregion               
    }
}
