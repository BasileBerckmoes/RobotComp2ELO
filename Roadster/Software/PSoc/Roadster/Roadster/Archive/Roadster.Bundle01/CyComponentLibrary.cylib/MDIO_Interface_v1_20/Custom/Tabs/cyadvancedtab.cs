/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace MDIO_Interface_v1_20.Tabs
{
    public partial class CyAdvancedTab : CyEditingWrapperControl
    {
        #region Constants
        private const int COL_ADDRESS = 0;
        private const int COL_INITIAL_VALUE = 1;
        private const int COL_MASK_VALUE = 2;
        private const int COL_CLEAR_ON_READ = 3;
        private const int COL_WRITE_ONLY = 4;
        private const int COL_TRIGGER_ON_WRITE = 5;
        private const int COL_TRIGGER_ON_READ = 6;
        private const int COL_AUX_BITS = 7;
        private const int DEFAULT_TABLE_HEADER_HEIGHT = 50;
        #endregion

        #region Class members
        private List<int> m_colsumnsNeedValidation;
        private CheckBox m_chbMaskHeader;
        private CheckBox m_chbClearOnReadHeader;
        private CheckBox m_chbWriteOnlyHeader;
        private CheckBox m_chbTriggerOnWriteHeader;
        private CheckBox m_chbTriggerOnReadHeader;
        private CyRegSpace m_selectedRegSpace;
        #endregion

        #region Class properties
        public override string TabName
        {
            get { return CyCustomizer.ADVANCED_TAB_NAME; }
        }
        #endregion

        #region Constructor(s)
        public CyAdvancedTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params = param;
            m_params.m_advancedTab = this;
            InitializeComponent();

            // Create a list with column indexes that will need validation
            m_colsumnsNeedValidation = new List<int>(new int[] { COL_INITIAL_VALUE, COL_MASK_VALUE, COL_AUX_BITS });

            // Initialize data grid view
            dgvRegisters.AutoGenerateColumns = false;
            dgvRegisters.EditMode = DataGridViewEditMode.EditOnEnter;
            dgvRegisters.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            foreach (DataGridViewColumn item in dgvRegisters.Columns)
            {
                item.SortMode = DataGridViewColumnSortMode.NotSortable; // prevent data grid from sorting
            }

            // Initialize comboboxes
            cbMemoryType.Items.Clear();
            cbMemoryType.DataSource = Enum.GetValues(typeof(CyEMemoryType));
            cbDataWidth.Items.Clear();
            cbDataWidth.DataSource = Enum.GetValues(typeof(CyEDataWidthType));
            cbConfigType.Items.Clear();
            cbConfigType.DataSource = Enum.GetValues(typeof(CyEMemoryType));

            InitializeHeaderCheckBoxes();
            UpdateUI();
        }
        #endregion Constructor(s)

        #region Validation
        private bool ValidateRow(int rowIndex)
        {
            bool isOk = true;
            for (int colIndex = 0; colIndex < m_colsumnsNeedValidation.Count; colIndex++)
            {
                isOk &= RangeCheck(rowIndex, m_colsumnsNeedValidation[colIndex]);
            }
            return isOk;
        }

        private bool ValidateColumn(int colIndex)
        {
            bool isOk = true;
            for (int rowIndex = 0; rowIndex < dgvRegisters.Rows.Count; rowIndex++)
            {
                isOk &= RangeCheck(rowIndex, colIndex);
            }
            return isOk;
        }

        public bool ValidateAllTable()
        {
            bool prevEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            bool isOk = true;
            for (int i = 0; i < dgvRegisters.Rows.Count; i++)
            {
                isOk &= ValidateRow(i);
            }
            m_params.GlobalEditMode = prevEditMode;
            return isOk;
        }

        private void CleanColumnErrors(int colIndex)
        {
            // Remove errors from grayed out cells
            for (int i = 0; i < dgvRegisters.Rows.Count; i++)
            {
                dgvRegisters[colIndex, i].ErrorText = "";
            }
        }

        private bool RangeCheck(int rowIndex, int colIndex)
        {
            CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
            if (regSpace == null) return false;
            ushort? currCellValue = null;
            UInt16 min = 0;
            UInt16 max = (regSpace.DataWidth == CyEDataWidthType.BIT_8) ? byte.MaxValue : UInt16.MaxValue;
            string message;
            if (colIndex == COL_INITIAL_VALUE)
            {
                message = Resources.InitialValueOutOfRange;
                currCellValue = regSpace.AddressConfig[rowIndex].InitValue;
            }
            else if (colIndex == COL_MASK_VALUE)
            {
                message = Resources.MaskValueOutOfRange;
                currCellValue = regSpace.AddressConfig[rowIndex].Mask;
            }
            else if ((colIndex == COL_AUX_BITS) && m_params.EnableAuxBits)
            {
                max = 0x0F; // maximum equals max 4-bit value
                message = Resources.AuxBitsOutOfRange;
                currCellValue = regSpace.AddressConfig[rowIndex].AuxBits;
            }
            else
            {
                return true;
            }

            if (dgvRegisters[colIndex, rowIndex].ReadOnly == false) // do not validate read-only cells
            {
                // If it is one of the columns that have to be checked than highlight or hide error provider
                if ((currCellValue.HasValue == false) || (currCellValue < min || currCellValue > max))
                {
                    if (colIndex == COL_AUX_BITS)
                    {
                        dgvRegisters[colIndex, rowIndex].ErrorText = string.Format(message,
                           CyParameters.ConvertDecToBin((byte)min, true),
                           CyParameters.ConvertDecToBin((byte)max, true));
                    }
                    else if (regSpace.DataWidth == CyEDataWidthType.BIT_8)
                    {
                        dgvRegisters[colIndex, rowIndex].ErrorText = string.Format(message,
                            CyParameters.ConvertDecToHex((byte)min), CyParameters.ConvertDecToHex((byte)max));
                    }
                    else
                    {
                        dgvRegisters[colIndex, rowIndex].ErrorText = string.Format(message,
                            CyParameters.ConvertDecToHex(min), CyParameters.ConvertDecToHex(max));
                    }
                    return false;
                }
                else
                {
                    dgvRegisters[colIndex, rowIndex].ErrorText = string.Empty;
                    return true;
                }
            }
            return true;
        }
        #endregion Validation

        #region Update GUI from data
        public void UpdateUI()
        {
            listBoxRegSpaces.Items.Clear();
            for (int i = 0; i < m_params.m_regSpaceList.m_regSpaces.Count; i++)
            {
                AddNewRegSpace(m_params.m_regSpaceList.m_regSpaces[i]);
            }
            if (listBoxRegSpaces.Items.Count > 0)
            {
                listBoxRegSpaces.SelectedIndex = 0;
            }
            chbEnableAuxBits.Checked = m_params.EnableAuxBits;
            ValidateAllTable();
        }

        private void UpdateRegSpaceSettingsUI(CyRegSpace regSpace)
        {
            bool prevEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            if (regSpace == null)
            {
                tbName.Text = String.Empty;
                tbStartAddress.Text = String.Empty;
                tbEndAddress.Text = String.Empty;
                cbMemoryType.SelectedItem = null;
                cbDataWidth.SelectedItem = null;
                cbConfigType.SelectedItem = null;
                gbRegisters.Enabled = false;
                gbRegSpaceSettings.Enabled = false;
            }
            else
            {
                tbName.Text = regSpace.Name;
                tbStartAddress.Text = regSpace.StartAddress.HasValue ?
                                      CyParameters.ConvertDecToHexWithoutPrefix(regSpace.StartAddress) : String.Empty;
                tbEndAddress.Text = regSpace.EndAddress.HasValue ?
                                      CyParameters.ConvertDecToHexWithoutPrefix(regSpace.EndAddress) : String.Empty;
                cbDataWidth.SelectedItem = regSpace.DataWidth;
                cbConfigType.SelectedItem = regSpace.ConfigType;
                UpdateRegistersTable(regSpace);
                if (cbMemoryType.SelectedItem != null &&
                    (CyEMemoryType)cbMemoryType.SelectedItem == regSpace.MemoryType)
                {
                    UpdateDataGridAppearance(regSpace);
                }
                else
                {
                    cbMemoryType.SelectedItem = regSpace.MemoryType;
                }
                gbRegisters.Enabled = true;
                gbRegSpaceSettings.Enabled = true;
                UpdateHeaderCheckBoxesState(regSpace);
            }
            m_params.GlobalEditMode = prevEditMode;
        }

        public void UpdateRegistersTable(CyRegSpace regSpace)
        {
            bool prevEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            dgvRegisters.DataSource = null;
            dgvRegisters.DataSource = regSpace.AddressConfig;
            for (int i = 0; i < dgvRegisters.Columns.Count; i++)
            {
                dgvRegisters.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                dgvRegisters.Columns[i].HeaderCell.Style.Alignment = DataGridViewContentAlignment.MiddleCenter;
                dgvRegisters.ColumnHeadersHeight = DEFAULT_TABLE_HEADER_HEIGHT;
            }

            SetColumnReadonlyState(COL_ADDRESS, true);
            UpdateColumnAuxBitsVisibility();
            m_params.GlobalEditMode = prevEditMode;
        }

        public void UpdateUIFromExprView()
        {
            chbEnableAuxBits.Checked = m_params.EnableAuxBits;
        }


        private void SetColumnReadonlyState(int colIndex, bool isReadonly)
        {
            dgvRegisters.Columns[colIndex].DefaultCellStyle.BackColor = isReadonly ?
                CyParameters.DISABLED_COLUMN_COLOR : CyParameters.ENABLED_COLUMN_COLOR;
            dgvRegisters.Columns[colIndex].ReadOnly = isReadonly;
        }

        private void UpdateColumnAuxBitsVisibility()
        {
            dgvRegisters.Columns[COL_AUX_BITS].Visible = m_params.EnableAuxBits;
        }
        #endregion Update GUI from data

        #region Update data from GUI
        private void SetRegSpaceSettings(CyRegSpace regSpace)
        {
            if ((regSpace == null) || m_params.GlobalEditMode == false) return;
            regSpace.Name = tbName.Text;
            regSpace.StartAddress = CyParameters.ConvertHexToDec(tbStartAddress.Text);
            regSpace.EndAddress = CyParameters.ConvertHexToDec(tbEndAddress.Text);
            if (cbMemoryType.SelectedItem != null)
            {
                regSpace.MemoryType = (CyEMemoryType)cbMemoryType.SelectedItem;
                regSpace.DataWidth = (CyEDataWidthType)cbDataWidth.SelectedItem;
                regSpace.ConfigType = (CyEMemoryType)cbConfigType.SelectedItem;
            }
            m_params.SetRegSpace(regSpace);
        }
        #endregion

        #region Add/Remove register space
        private void AddNewRegSpace(CyRegSpace newRegSpace)
        {
            if (newRegSpace == null)
            {
                string newName = m_params.m_regSpaceList.GetNextDefaultName();
                newRegSpace = new CyRegSpace(newName);
                newRegSpace.m_paramIndex = m_params.m_regSpaceList.m_regSpaces.Count;
                m_params.m_regSpaceList.m_regSpaces.Add(newRegSpace);
            }
            listBoxRegSpaces.Items.Add(newRegSpace);
            UpdateToolStripButtonsEnabling();
            m_params.SetRegSpace(newRegSpace);
        }

        private void RemoveRegSpace(CyRegSpace regSpace)
        {
            if (regSpace == null || listBoxRegSpaces.Items.Count == 1) return;

            // Remove register space
            Cursor prevCursor = Cursor.Current;
            Cursor.Current = Cursors.WaitCursor;
            int regSpaceIndex = listBoxRegSpaces.Items.IndexOf(regSpace);
            listBoxRegSpaces.Items.Remove(regSpace);
            m_params.m_regSpaceList.m_regSpaces.Remove(regSpace);

            // Set nearest register space as active if exists
            if (listBoxRegSpaces.Items.Count > 0)
            {
                listBoxRegSpaces.SelectedIndex = Math.Min(regSpaceIndex, listBoxRegSpaces.Items.Count - 1);
            }

            // Rearrange parameters
            for (int i = regSpaceIndex; i < CyRegSpaceConfig.MAX_REG_SPACE_NUM; i++)
            {
                if (i >= listBoxRegSpaces.Items.Count)
                {
                    m_params.ClearRegSpaceParam(i);
                }
                else
                {
                    CyRegSpace listItem = (CyRegSpace)listBoxRegSpaces.Items[i];
                    listItem.m_paramIndex = i;
                    m_params.SetRegSpace(listItem);
                }
            }
            Cursor.Current = prevCursor;
            UpdateToolStripButtonsEnabling();
        }

        private void UpdateToolStripButtonsEnabling()
        {
            toolStripButtonAdd.Enabled =
                ((listBoxRegSpaces.Items.Count == CyRegSpaceConfig.MAX_REG_SPACE_NUM) == false);
            toolStripButtonRemove.Enabled = (listBoxRegSpaces.Items.Count > 1);
        }
        #endregion Add/Remove register space

        #region Datagrid event handlers
        private void dgvRegisters_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (listBoxRegSpaces.SelectedItem != null)
            {
                CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
                m_params.SetRegSpace(regSpace);
                RangeCheck(e.RowIndex, e.ColumnIndex);
                if (e.ColumnIndex != COL_INITIAL_VALUE)
                {
                    bool prevEditMode = m_params.GlobalEditMode;
                    m_params.GlobalEditMode = false;
                    UpdateHeaderCheckBoxesState(regSpace);
                    m_params.GlobalEditMode = prevEditMode;
                }
            }
        }

        private void dgvRegisters_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(dgvRegisters);
        }

        private void dgvRegisters_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (e.ColumnIndex == COL_ADDRESS && e.Value != null)
            {
                UInt16 value = 0;
                if (UInt16.TryParse(e.Value.ToString(), out value))
                {
                    e.Value = "0x" + value.ToString("X4");
                    e.FormattingApplied = true;
                }
            }
        }

        private void dgvRegisters_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            if (e.RowIndex < 0 && e.ColumnIndex == COL_MASK_VALUE)
                SetHeaderCheckBoxLocation(e.ColumnIndex, e.RowIndex, m_chbMaskHeader);
            if (e.RowIndex < 0 && e.ColumnIndex == COL_CLEAR_ON_READ)
                SetHeaderCheckBoxLocation(e.ColumnIndex, e.RowIndex, m_chbClearOnReadHeader);
            if (e.RowIndex < 0 && e.ColumnIndex == COL_WRITE_ONLY)
                SetHeaderCheckBoxLocation(e.ColumnIndex, e.RowIndex, m_chbWriteOnlyHeader);
            if (e.RowIndex < 0 && e.ColumnIndex == COL_TRIGGER_ON_WRITE)
                SetHeaderCheckBoxLocation(e.ColumnIndex, e.RowIndex, m_chbTriggerOnWriteHeader);
            if (e.RowIndex < 0 && e.ColumnIndex == COL_TRIGGER_ON_READ)
                SetHeaderCheckBoxLocation(e.ColumnIndex, e.RowIndex, m_chbTriggerOnReadHeader);
        }
        #endregion Datagrid event handlers

        #region Toolstrip event handlers
        private void toolStripButtonAdd_Click(object sender, EventArgs e)
        {
            AddNewRegSpace(null);
            listBoxRegSpaces.SelectedIndex = listBoxRegSpaces.Items.Count - 1;
        }

        private void toolStripButtonRemove_Click(object sender, EventArgs e)
        {
            RemoveRegSpace((CyRegSpace)listBoxRegSpaces.SelectedItem);
        }

        private void toolStripButtonImport_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = Resources.FilterDialogImportTitle;
            openFileDialog.DefaultExt = Resources.FileDialogExt;
            openFileDialog.Filter = Resources.FileDialogFilter;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                DialogResult dr = MessageBox.Show(Resources.ImportConfirmation, Resources.MsgWarningTitle,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (dr == DialogResult.Yes)
                {
                    Cursor currentCursor = Cursor.Current;
                    Cursor.Current = Cursors.WaitCursor;
                    m_params.Import(openFileDialog.FileName);
                    UpdateUI();
                    if (listBoxRegSpaces.Items.Count > 0)
                        listBoxRegSpaces.SelectedIndex = 0;
                    Cursor.Current = currentCursor;
                    UpdateToolStripButtonsEnabling();
                }
            }
        }

        private void toolStripButtonExport_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Title = Resources.FilterDialogExportTitle;
            saveFileDialog.DefaultExt = Resources.FileDialogExt;
            saveFileDialog.Filter = Resources.FileDialogFilter;
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.FileName = Resources.DefaultXMLFileName;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                Cursor currentCursor = Cursor.Current;
                Cursor.Current = Cursors.WaitCursor;
                m_params.Export(saveFileDialog.FileName);
                Cursor.Current = currentCursor;
            }
        }
        #endregion

        #region Register space event handlers
        private void cbComboBoxes_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
            SetRegSpaceSettings(regSpace);

            if (regSpace != null)
            {
                if (m_params.GlobalEditMode)
                {
                    // Update and validate table
                    if ((sender == cbDataWidth))
                    {
                        UpdateRegistersTable(regSpace);
                        UpdateDataGridAppearance(regSpace);
                        ValidateAllTable();
                        UpdateHeaderCheckBoxesState(regSpace, false);
                    }
                }

                // Disable/Enable all columns except Init value
                if (sender == cbMemoryType)
                {
                    UpdateDataGridAppearance(regSpace);
                    bool readOnly = (regSpace.MemoryType == CyEMemoryType.FLASH);
                    if (readOnly)
                    {
                        CleanColumnErrors(COL_MASK_VALUE);
                        CleanColumnErrors(COL_AUX_BITS);
                    }
                    else
                    {
                        ValidateAllTable();
                    }
                }
            }
        }

        private void cb_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = CyParameters.GetEnumDisplayName(e.ListItem);
        }

        private void UpdateDataGridAppearance(CyRegSpace regSpace)
        {
            bool readOnly = (regSpace.MemoryType == CyEMemoryType.FLASH);
            SetColumnReadonlyState(COL_MASK_VALUE, readOnly);
            SetColumnReadonlyState(COL_CLEAR_ON_READ, readOnly);
            SetColumnReadonlyState(COL_WRITE_ONLY, readOnly);
            SetColumnReadonlyState(COL_TRIGGER_ON_WRITE, readOnly);
            SetColumnReadonlyState(COL_TRIGGER_ON_READ, readOnly);
            SetColumnReadonlyState(COL_AUX_BITS, readOnly);
            m_chbMaskHeader.Enabled = (readOnly == false);
            m_chbClearOnReadHeader.Enabled = (readOnly == false);
            m_chbWriteOnlyHeader.Enabled = (readOnly == false);
            m_chbTriggerOnWriteHeader.Enabled = (readOnly == false);
            m_chbTriggerOnReadHeader.Enabled = (readOnly == false);
        }

        private void tbName_TextChanged(object sender, EventArgs e)
        {
            CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
            if (regSpace != null)
            {
                if (m_params.GlobalEditMode)
                {
                    regSpace.Name = tbName.Text;
                }
                m_errorProvider.SetError(tbName, m_params.m_regSpaceList.GetNameError(regSpace));
            }
        }

        private void tbName_Validated(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode == false) return;
            // Set input value
            if (listBoxRegSpaces.SelectedIndex >= 0)
            {
                listBoxRegSpaces.RefreshItem(listBoxRegSpaces.SelectedIndex);
                SetRegSpaceSettings((CyRegSpace)listBoxRegSpaces.SelectedItem);
            }
        }

        private void tbStartEndAddress_TextChanged(object sender, EventArgs e)
        {
            TextBox currentTextBox = (TextBox)sender;
            if (listBoxRegSpaces.Items.Count > 0)
            {
                String sanityCheckMessage = String.Empty;
                // Check if start address is not greater than end address
                if (String.IsNullOrEmpty(tbStartAddress.Text) == false &&
                    String.IsNullOrEmpty(tbEndAddress.Text) == false)
                {
                    if (CyParameters.ConvertHexToDec(tbStartAddress.Text, false) >
                        CyParameters.ConvertHexToDec(tbEndAddress.Text, false))
                        sanityCheckMessage = Resources.SanityCheck;
                }
                // Check if input address is in range
                ushort? value = CyParameters.ConvertHexToDec(currentTextBox.Text, false);
                if (value == null ||
                    value < CyParamRanges.START_END_ADDRESS_MIN || value > CyParamRanges.START_END_ADDRESS_MAX)
                {
                    m_errorProvider.SetError(currentTextBox, String.Format(Resources.StartEndAddressOutOfRange,
                        CyParameters.ConvertDecToHex(CyParamRanges.START_END_ADDRESS_MIN),
                        CyParameters.ConvertDecToHex(CyParamRanges.START_END_ADDRESS_MAX)));
                }
                else if (String.IsNullOrEmpty(sanityCheckMessage) == false)
                {
                    m_errorProvider.SetError(tbStartAddress, Resources.SanityCheck);
                    m_errorProvider.SetError(tbEndAddress, Resources.SanityCheck);
                }
                else
                {
                    // Clear error provider for both textboxes if sanity check error was corrected
                    if (m_errorProvider.GetError(tbStartAddress) == Resources.SanityCheck ||
                        m_errorProvider.GetError(tbEndAddress) == Resources.SanityCheck)
                    {
                        m_errorProvider.SetError(tbStartAddress, String.Empty);
                        m_errorProvider.SetError(tbEndAddress, String.Empty);
                    }
                    else
                    {
                        m_errorProvider.SetError(currentTextBox, String.Empty);
                    }
                }
                // Set new value to parameter and update datagrid rows
                if (m_params.GlobalEditMode && listBoxRegSpaces.SelectedIndex >= 0)
                {
                    CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;

                    SetRegSpaceSettings(regSpace);
                    if (m_errorProvider.GetError(tbStartAddress) == String.Empty &&
                        m_errorProvider.GetError(tbEndAddress) == String.Empty)
                    {
                        UpdateRegistersTable(regSpace);
                        UpdateDataGridAppearance(regSpace);
                        ValidateAllTable();
                        UpdateHeaderCheckBoxesState(regSpace);
                    }
                }
            }
            else
            {
                m_errorProvider.SetError(currentTextBox, string.Empty);
            }
        }

        private void tbStartEndAddress_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 'a' || e.KeyChar == 'b' || e.KeyChar == 'c' ||
                e.KeyChar == 'd' || e.KeyChar == 'e' || e.KeyChar == 'f')
            {
                e.KeyChar = e.KeyChar.ToString().ToUpper()[0];
            }
        }

        private void chbEnableAuxBits_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableAuxBits = chbEnableAuxBits.Checked;
            m_params.m_regSpaceList.m_enableAuxBits = m_params.EnableAuxBits;
            UpdateColumnAuxBitsVisibility();
            if (m_params.EnableAuxBits)
            {
                ValidateColumn(COL_AUX_BITS);
            }
            else
            {
                ResetAuxBits();
            }
        }

        /// <summary>
        /// If some cells contain wrong values, reset that values to default
        /// </summary>
        private void ResetAuxBits()
        {
            for (int i = 0; i < m_params.m_regSpaceList.m_regSpaces.Count; i++)
                for (int j = 0; j < m_params.m_regSpaceList.m_regSpaces[i].m_addressConfig.Count; j++)
                {
                    CyRegAddress reg = m_params.m_regSpaceList.m_regSpaces[i].m_addressConfig[j];
                    if (reg.AuxBits == null)
                    {
                        m_params.m_regSpaceList.m_regSpaces[i].m_addressConfig[j].AuxBitsDisplay =
                            "".PadLeft(CyRegAddress.AUX_BITS_COUNT, '0');
                    }
                }
        }
        #endregion

        #region Other controls event handlers
        private void listBoxRegSpaces_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
            if (regSpace != null && regSpace != m_selectedRegSpace)
            {
                UpdateRegSpaceSettingsUI(regSpace);
                if (m_params.GlobalEditMode)
                {
                    Cursor prevCursor = Cursor.Current;
                    Cursor.Current = Cursors.WaitCursor;
                    ValidateAllTable();
                    Cursor.Current = prevCursor;
                }
                m_selectedRegSpace = regSpace;
            }
        }

        private void listBoxRegSpaces_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = ((CyRegSpace)e.ListItem).Name;
        }

        private void CyAdvancedTab_Load(object sender, EventArgs e)
        {
            if (m_params.IsRegSpaceDefault)
            {
                foreach (CyRegSpace item in m_params.m_regSpaceList.m_regSpaces)
                {
                    m_params.SetRegSpace(item);
                }
            }
        }
        #endregion Other controls event handlers

        #region Header checkboxes methods
        private void InitializeHeaderCheckBoxes()
        {
            // Create header check boxes
            m_chbMaskHeader = new CheckBox();
            m_chbClearOnReadHeader = new CheckBox();
            m_chbWriteOnlyHeader = new CheckBox();
            m_chbTriggerOnWriteHeader = new CheckBox();
            m_chbTriggerOnReadHeader = new CheckBox();
            // Avoid focus on control
            m_chbMaskHeader.TabIndex = 0;
            m_chbClearOnReadHeader.TabIndex = 1;
            m_chbWriteOnlyHeader.TabIndex = 2;
            m_chbTriggerOnWriteHeader.TabIndex = 3;
            m_chbTriggerOnReadHeader.TabIndex = 4;
            // Set text for checkboxes
            m_chbMaskHeader.Text = Resources.ColHeaderMaskValue;
            m_chbClearOnReadHeader.Text = Resources.ColHeaderClearOnRead;
            m_chbWriteOnlyHeader.Text = Resources.ColHeaderWriteOnly;
            m_chbTriggerOnWriteHeader.Text = Resources.ColHeaderTriggerOnWrite;
            m_chbTriggerOnReadHeader.Text = Resources.ColHeaderTriggerOnRead;
            // Make checkboxes transparent
            m_chbMaskHeader.BackColor = Color.Transparent;
            m_chbClearOnReadHeader.BackColor = Color.Transparent;
            m_chbWriteOnlyHeader.BackColor = Color.Transparent;
            m_chbTriggerOnWriteHeader.BackColor = Color.Transparent;
            m_chbTriggerOnReadHeader.BackColor = Color.Transparent;
            // Add the check boxes into the DataGridView
            this.dgvRegisters.Controls.Add(m_chbMaskHeader);
            this.dgvRegisters.Controls.Add(m_chbClearOnReadHeader);
            this.dgvRegisters.Controls.Add(m_chbWriteOnlyHeader);
            this.dgvRegisters.Controls.Add(m_chbTriggerOnWriteHeader);
            this.dgvRegisters.Controls.Add(m_chbTriggerOnReadHeader);
            // Create events for check boxes
            m_chbMaskHeader.CheckedChanged += headerCheckBox_CheckedChanged;
            m_chbClearOnReadHeader.CheckedChanged += headerCheckBox_CheckedChanged;
            m_chbWriteOnlyHeader.CheckedChanged += headerCheckBox_CheckedChanged;
            m_chbTriggerOnWriteHeader.CheckedChanged += headerCheckBox_CheckedChanged;
            m_chbTriggerOnReadHeader.CheckedChanged += headerCheckBox_CheckedChanged;
        }

        private void headerCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                m_params.GlobalEditMode = false;
                CheckBox currentCheckBox = (CheckBox)sender;
                bool isChecked = currentCheckBox.Checked;
                CyRegSpace regSpace = (CyRegSpace)listBoxRegSpaces.SelectedItem;
                if (sender == m_chbMaskHeader)
                {
                    string newValue = isChecked ? ((regSpace.DataWidth == CyEDataWidthType.BIT_8) ?
                        "0x00FF" : "0xFFFF") : "0x0000";
                    for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                    {
                        regSpace.AddressConfig[addrConfigIndex].MaskDisplay = newValue;
                    }
                    ValidateColumn(COL_MASK_VALUE);
                }
                else if (sender == m_chbClearOnReadHeader)
                {
                    for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                    {
                        regSpace.AddressConfig[addrConfigIndex].ClearOnRead = isChecked;
                    }
                }
                else if (sender == m_chbWriteOnlyHeader)
                {
                    for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                    {
                        regSpace.AddressConfig[addrConfigIndex].WriteOnly = isChecked;
                    }
                }
                else if (sender == m_chbTriggerOnWriteHeader)
                {
                    for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                    {
                        regSpace.AddressConfig[addrConfigIndex].TriggerOnWrite = isChecked;
                    }
                }
                else if (sender == m_chbTriggerOnReadHeader)
                {
                    for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                    {
                        regSpace.AddressConfig[addrConfigIndex].TriggerOnRead = isChecked;
                    }
                }
                dgvRegisters.RefreshEdit();
                dgvRegisters.Refresh();
                m_params.GlobalEditMode = true;
                m_params.SetRegSpace(regSpace);
                UpdateToolTips();
            }
        }

        private void UpdateToolTips()
        {
            toolTip.SetToolTip(m_chbMaskHeader, m_chbMaskHeader.Checked ?
                                            Resources.ToolTipUnmaskAll : Resources.ToolTipMaskAll);
            toolTip.SetToolTip(m_chbClearOnReadHeader, m_chbClearOnReadHeader.Checked ?
                                            Resources.ToolTipClearOnReadNone : Resources.ToolTipClearOnReadAll);
            toolTip.SetToolTip(m_chbWriteOnlyHeader, m_chbWriteOnlyHeader.Checked ?
                                            Resources.ToolTipWriteOnlyNone : Resources.ToolTipWriteOnlyAll);
            toolTip.SetToolTip(m_chbTriggerOnWriteHeader, m_chbTriggerOnWriteHeader.Checked ?
                                            Resources.ToolTipTriggerOnWriteNone : Resources.ToolTipTriggerOnWriteAll);
            toolTip.SetToolTip(m_chbTriggerOnReadHeader, m_chbTriggerOnReadHeader.Checked ?
                                            Resources.ToolTipTriggerOnReadNone : Resources.ToolTipTriggerOnReadAll);
        }

        private void SetHeaderCheckBoxLocation(int colIndex, int rowIndex, CheckBox checkBox)
        {
            Rectangle oRectangle = dgvRegisters.GetCellDisplayRectangle(colIndex, rowIndex, true);
            Point oPoint = oRectangle.Location;
            //oPoint.X = oRectangle.Location.X + (oRectangle.Width - m_chbClearOnReadHeader.Width) / 2;
            //oPoint.Y = oRectangle.Location.Y + (oRectangle.Height - m_chbClearOnReadHeader.Height) / 2;
            checkBox.Location = oPoint;
            checkBox.Width = oRectangle.Width/* - 5*/;
            checkBox.Height = oRectangle.Height/* - 10*/;
        }

        private void UpdateHeaderCheckBoxesState(CyRegSpace regSpace)
        {
            UpdateHeaderCheckBoxesState(regSpace, true);
        }
        private void UpdateHeaderCheckBoxesState(CyRegSpace regSpace, bool updateHeaderForBooleanFields)
        {
            bool allMaskValuesMaximum = true;
            bool allClearOnReadChecked = true;
            bool allWriteOnlyChecked = true;
            bool allTriggerOnWriteChecked = true;
            bool allTriggerOnReadChecked = true;
            UInt16 maxValue = (ushort)((regSpace.DataWidth == CyEDataWidthType.BIT_8) ? 0xFF : 0xFFFF);
            for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
            {
                if (regSpace.AddressConfig[addrConfigIndex].Mask != maxValue && allMaskValuesMaximum)
                {
                    allMaskValuesMaximum = false;
                }
                if (updateHeaderForBooleanFields)
                {
                    if (regSpace.AddressConfig[addrConfigIndex].ClearOnRead == false && allClearOnReadChecked)
                    {
                        allClearOnReadChecked = false;
                    }
                    if (regSpace.AddressConfig[addrConfigIndex].WriteOnly == false && allWriteOnlyChecked)
                    {
                        allWriteOnlyChecked = false;
                    }
                    if (regSpace.AddressConfig[addrConfigIndex].TriggerOnWrite == false && allTriggerOnWriteChecked)
                    {
                        allTriggerOnWriteChecked = false;
                    }
                    if (regSpace.AddressConfig[addrConfigIndex].TriggerOnRead == false && allTriggerOnReadChecked)
                    {
                        allTriggerOnReadChecked = false;
                    }
                }
            }
            bool prevEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            m_chbMaskHeader.Checked = allMaskValuesMaximum;
            if (updateHeaderForBooleanFields)
            {
                m_chbClearOnReadHeader.Checked = allClearOnReadChecked;
                m_chbWriteOnlyHeader.Checked = allWriteOnlyChecked;
                m_chbTriggerOnWriteHeader.Checked = allTriggerOnWriteChecked;
                m_chbTriggerOnReadHeader.Checked = allTriggerOnReadChecked;
            }
            m_params.GlobalEditMode = prevEditMode;
            UpdateToolTips();
        }
        #endregion

        #region Overriden method(s)
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (toolStripRegSpace == null)
                return base.ProcessCmdKey(ref msg, keyData);

            bool result = true;

            if (keyData == (Keys.Alt | Keys.D))
            {
                toolStripButtonAdd.PerformClick();
            }
            else if (keyData == (Keys.Alt | Keys.R))
            {
                toolStripButtonRemove.PerformClick();
            }
            else if (keyData == (Keys.Control | Keys.M))
            {
                toolStripButtonImport.PerformClick();
            }
            else if (keyData == (Keys.Control | Keys.R))
            {
                toolStripButtonExport.PerformClick();
            }
            else if (keyData == (Keys.Alt | Keys.C))
            {
                if (dgvRegisters.CurrentCell.ColumnIndex == COL_MASK_VALUE)
                {
                    m_chbMaskHeader.Checked = (m_chbMaskHeader.Checked == false);
                }
                else if (dgvRegisters.CurrentCell.ColumnIndex == COL_CLEAR_ON_READ)
                {
                    m_chbClearOnReadHeader.Checked = (m_chbClearOnReadHeader.Checked == false);
                }
                else if (dgvRegisters.CurrentCell.ColumnIndex == COL_WRITE_ONLY)
                {
                    m_chbWriteOnlyHeader.Checked = (m_chbWriteOnlyHeader.Checked == false);
                }
                else if (dgvRegisters.CurrentCell.ColumnIndex == COL_TRIGGER_ON_WRITE)
                {
                    m_chbTriggerOnWriteHeader.Checked = (m_chbTriggerOnWriteHeader.Checked == false);
                }
                else if (dgvRegisters.CurrentCell.ColumnIndex == COL_TRIGGER_ON_READ)
                {
                    m_chbTriggerOnReadHeader.Checked = (m_chbTriggerOnReadHeader.Checked == false);
                }
            }
            else
            {
                result = base.ProcessCmdKey(ref msg, keyData);
            }

            return result;
        }
        #endregion
    }

    public class CyRefreshingListBox : ListBox
    {
        public new void RefreshItem(int index)
        {
            base.RefreshItem(index);
        }
    }
}
