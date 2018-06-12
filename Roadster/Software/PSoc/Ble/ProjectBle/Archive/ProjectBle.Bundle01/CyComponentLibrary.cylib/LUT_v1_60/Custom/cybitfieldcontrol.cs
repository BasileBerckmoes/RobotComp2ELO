/*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Linq;
using CyDesigner.Extensions.Common;

namespace LUT_v1_60
{
    internal partial class CyBitfieldControl : CyTabBase
    {
        private const string PARAM_TAB_NAME = "Basic";

        public const int HEX_INPUT_COLUMN = 0;
        public const int INPUT_COLUMNS_START = HEX_INPUT_COLUMN + 1;
        public const int INPUT_COLUMNS_END = CyLutTable.MAX_INPUTS + INPUT_COLUMNS_START - 1;
        public const int EMPTY_MIDDLE_COLUMN = INPUT_COLUMNS_END + 1;
        public const int OUTPUT_COLUMNS_START = INPUT_COLUMNS_END + 2; // Need room for divider column
        public const int OUTPUT_COLUMNS_END = OUTPUT_COLUMNS_START + CyLutTable.MAX_OUTPUTS - 1;
        public const int HEX_OUTPUT_COLUMN = OUTPUT_COLUMNS_END + 1;

        private TextBox m_tbColumnRename; 
        private int m_clickedColumnIndex = 0;

        public CyBitfieldControl() :
            base(null, PARAM_TAB_NAME, ResourceMsg.TabDisplayNameConfigure)
        {
            InitializeComponent();
        }

        public CyBitfieldControl(CyParameters parameters) :
            base(parameters, PARAM_TAB_NAME, ResourceMsg.TabDisplayNameConfigure)
        {
            InitializeComponent();
            InitControls();
        }

        #region Form Initialization
        private void InitControls()
        {
            m_dgvLutTable.RowHeadersVisible = false;
            m_dgvLutTable.AllowUserToAddRows = false;
            m_dgvLutTable.AllowUserToOrderColumns = false;
            m_dgvLutTable.AllowUserToResizeColumns = false;
            m_dgvLutTable.AllowUserToResizeRows = false;
            
            SetupColumns();
            InitRenameTextBox();

            CyUtils.SetNumericMinMax(m_nudInputs, 1, CyLutTable.MAX_INPUTS);
            CyUtils.SetNumericMinMax(m_nudOutputs, 1, CyLutTable.MAX_OUTPUTS);
            m_nudInputs.TextChanged += m_nudInputs_TextChanged;
            m_nudOutputs.TextChanged += m_nudOutputs_TextChanged;
        }
        
        void SetupColumns()
        {
            DataGridViewTextBoxColumn hexColumn = new DataGridViewTextBoxColumn();
            hexColumn.HeaderText = String.Format(ResourceMsg.DgvColumnNameInputHexValue);
            hexColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            hexColumn.ReadOnly = true;
            hexColumn.CellTemplate = new DataGridViewTextBoxCell();
            hexColumn.CellTemplate.Style.BackColor = Color.LightGray;
            m_dgvLutTable.Columns.Add(hexColumn);

            //Create the Inputs Columns
            for (int i = (CyLutTable.MAX_INPUTS - 1); i >= 0; i--)
            {
                DataGridViewTextBoxColumn inputColumn = new DataGridViewTextBoxColumn();
                inputColumn.HeaderText = m_params.GetInName(i);
                inputColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
                inputColumn.ReadOnly = true;
                inputColumn.CellTemplate = new DataGridViewTextBoxCell();
                inputColumn.CellTemplate.Style.BackColor = Color.LightGray;
                m_dgvLutTable.Columns.Add(inputColumn);
            }

            //Setup the Blank Divider Column
            DataGridViewTextBoxColumn dividerColumn = new DataGridViewTextBoxColumn();
            dividerColumn.HeaderText = String.Empty;
            dividerColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.None;
            dividerColumn.Width = 20;
            dividerColumn.ReadOnly = true;
            dividerColumn.CellTemplate = new DataGridViewTextBoxCell();
            dividerColumn.CellTemplate.Style.BackColor = Color.Black;
            m_dgvLutTable.Columns.Add(dividerColumn);
            //Create the Outputs Columns
            for (int i = (CyLutTable.MAX_OUTPUTS - 1); i >= 0; i--)
            {
                DataGridViewButtonColumn outputColumn = new DataGridViewButtonColumn();
                outputColumn.HeaderText = m_params.GetOutName(i);
                outputColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
                outputColumn.FlatStyle = FlatStyle.Flat;
                m_dgvLutTable.Columns.Add(outputColumn);
            }

            hexColumn = new DataGridViewTextBoxColumn();
            hexColumn.HeaderText = String.Format(ResourceMsg.DgvColumnNameOutputHexValue);
            hexColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            hexColumn.ReadOnly = false;
            hexColumn.CellTemplate = new DataGridViewTextBoxCell();
            hexColumn.CellTemplate.Style.BackColor = Color.White;
            hexColumn.Visible = true;

            m_dgvLutTable.Columns.Add(hexColumn);
        }

        /// <summary>
        /// Full update of the m_dgvLutTable based on the data from LutTable
        /// </summary>
        private void UpdateDgvFromLutTable()
        {
            m_dgvLutTable.SuspendLayout();

            m_dgvLutTable.Rows.Clear();
            for (int i = 0; i < m_params.LutTable.ActualRowCount; i++)
            {
                CyLutTableRow lutTableRow = m_params.LutTable.Rows[i];

                int newRowIndex = m_dgvLutTable.Rows.Add();
                DataGridViewRow newRow = m_dgvLutTable.Rows[newRowIndex];
                newRow.Tag = lutTableRow;

                newRow.Cells[HEX_INPUT_COLUMN].Value = lutTableRow.InputValue.ToString("X2");
                newRow.Cells[EMPTY_MIDDLE_COLUMN].Value = "";

                List<byte> inputBits = lutTableRow.GetInputBitsValues();
                inputBits.Reverse();
                for (int j = 0; j < CyLutTable.MAX_INPUTS; j++)
                {
                    newRow.Cells[INPUT_COLUMNS_START + j].Value = inputBits[j];
                }
            }
            SetOutputColumnsValues();

            SetInputColumnsVisibility();
            SetOutputColumnsVisibility();

            m_dgvLutTable.ResumeLayout();

            // Save the table to the parameters
            if (m_params.GlobalEditMode)
            {
                m_params.SaveLutTable();
            }
        }

        /// <summary>
        /// Show/hide input columns base don the number of inputs
        /// </summary>
        private void SetInputColumnsVisibility()
        {
            for (int i = 0; i < CyLutTable.MAX_INPUTS - m_params.NumInputs; i++)
            {
                m_dgvLutTable.Columns[INPUT_COLUMNS_START + i].Visible = false;
            }

            for (int i = CyLutTable.MAX_INPUTS - m_params.NumInputs; i < CyLutTable.MAX_INPUTS; i++)
            {
                m_dgvLutTable.Columns[INPUT_COLUMNS_START + i].Visible = true;
            }
        }

        /// <summary>
        /// Show/hide output columns based on the number of outputs
        /// </summary>
        private void SetOutputColumnsVisibility()
        {
            for (int i = OUTPUT_COLUMNS_START; i <= OUTPUT_COLUMNS_END; i++)
            {
                m_dgvLutTable.Columns[i].Visible = i > (OUTPUT_COLUMNS_END - m_params.NumOutputs);
            }
        }

        /// <summary>
        /// Update output bits and output hex columns based on the data from LutTable
        /// </summary>
        private void SetOutputColumnsValues()
        {
            for (int i = 0; i < m_dgvLutTable.RowCount; i++)
            {
                SetOutputColumnsValues(i);
            }
        }

        /// <summary>
        /// Update output bits and output hex columns for a particular row based on the data from LutTable
        /// </summary>
        private void SetOutputColumnsValues(int dgvRowIndex)
        {
            if (dgvRowIndex < m_dgvLutTable.RowCount)
            {
                DataGridViewRow dgvRow = m_dgvLutTable.Rows[dgvRowIndex];
                CyLutTableRow lutTableRow = dgvRow.Tag as CyLutTableRow;

                dgvRow.Cells[HEX_OUTPUT_COLUMN].Value = lutTableRow.OutputStr;

                for (int j = OUTPUT_COLUMNS_START; j <= OUTPUT_COLUMNS_END; j++)
                {
                    byte bitValue = lutTableRow.OutputBits[OUTPUT_COLUMNS_END - j];
                    dgvRow.Cells[j].Value = bitValue;
                    dgvRow.Cells[j].Style.BackColor = (bitValue == 0) ? Color.LightGray : Color.White;
                    dgvRow.Cells[j].Style.SelectionBackColor = dgvRow.Cells[j].Style.BackColor;
                    dgvRow.Cells[j].Style.SelectionForeColor = SystemColors.ControlText;
                }
            }
        }
        #endregion

        #region Form Update

        public override void UpdateUI()
        {
            CyUtils.SetNudValue(m_nudInputs, m_params.NumInputs);
            CyUtils.SetNudValue(m_nudOutputs, m_params.NumOutputs);
            m_chbxRegisterOutputs.Checked = m_params.RegisterOutputs;
            UpdateDgvFromLutTable();
        }

        private void SetAllButtonValues()
        {
            m_params.LutTable.SetOutput();
            UpdateDgvFromLutTable();
        }

        private void ClearAllButtonValues()
        {
            m_params.LutTable.ClearOutput();
            UpdateDgvFromLutTable();
        }
        #endregion Form Update

        #region Event handlers

        void m_nudInputs_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                string strValue = m_nudInputs.Text;
                int value;
                bool valid = CyUtils.ValidateNumeric(m_nudInputs, m_nudInputs.Minimum, m_nudInputs.Maximum,
                    m_errorProvider);

                if (Int32.TryParse(strValue, out value) && valid)
                {
                    m_params.NumInputs = value;
                    m_params.LutTable.ChangeInputCount(m_params.NumInputs);
                    UpdateDgvFromLutTable();
                }
            }
        }

        void m_nudOutputs_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                string strValue = m_nudOutputs.Text;
                int value;
                bool valid = CyUtils.ValidateNumeric(m_nudOutputs, m_nudOutputs.Minimum, m_nudOutputs.Maximum,
                    m_errorProvider);

                if (Int32.TryParse(strValue, out value) && valid)
                {
                    m_params.NumOutputs = value;
                    m_params.LutTable.ChangeOutputCount(m_params.NumOutputs);
                    UpdateDgvFromLutTable();
                }
            }
        }

        private void m_chbxRegisterOutputs_CheckedChanged(object sender, EventArgs e)
        {
            m_params.RegisterOutputs = m_chbxRegisterOutputs.Checked;
        }

        private void m_bSetAll_Click(object sender, EventArgs e)
        {
            SetAllButtonValues();
        }

        private void m_bClearAll_Click(object sender, EventArgs e)
        {
            ClearAllButtonValues();
        }


        private void m_bExport_Click(object sender, EventArgs e)
        {
            string tableContent = CyUtils.ExportDataGridToCsv(m_dgvLutTable);
            CyUtils.SaveToFile(tableContent);
        }
        
        private void m_dgvBitFieldConfigure_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
           
            if ((e.ColumnIndex >= OUTPUT_COLUMNS_START) && (e.ColumnIndex <= OUTPUT_COLUMNS_END))
            {
                DataGridViewRow dgvRow = m_dgvLutTable.Rows[e.RowIndex];
                CyLutTableRow lutTableRow = dgvRow.Tag as CyLutTableRow;

                lutTableRow.InvertOutputBit(OUTPUT_COLUMNS_END - e.ColumnIndex);
                SetOutputColumnsValues(e.RowIndex);

                // Save the table to the parameters
                m_params.SaveLutTable();
            }           
        }

        private void m_dgvBitFieldConfigure_CellEndEdit(object sender, EventArgs e)
        {
            DataGridViewCell currentCell = ((DataGridView)sender).CurrentCell;

            if (currentCell != null && currentCell.ColumnIndex == HEX_OUTPUT_COLUMN)
            {
                DataGridViewTextBoxCell cell = currentCell as DataGridViewTextBoxCell;
                string cellText = cell.Value == null ? "" : cell.Value.ToString();
               
                // Validate entered value
                byte newOutputValue;
                CyCustErr err = CyUtils.ConvertHexStrToByte(cellText, out newOutputValue);
                if (err.IsOK)
                {
                    byte maxValue = m_params.LutTable.GetMaxRowOutputValue();
                    if (newOutputValue > maxValue)
                    {
                        err = new CyCustErr(ResourceMsg.ErrorMsgWrongFormat);
                    }
                }

                // Save the value and update the dataGrid
                if (err.IsOK)
                {
                    CyLutTableRow lutTableRow = currentCell.OwningRow.Tag as CyLutTableRow;
                    lutTableRow.SetOutputBitsFromOutput(newOutputValue);
                }
                // If data is invalid, the column value would be reverted
                // If data is valid, update with a new value
                SetOutputColumnsValues(currentCell.RowIndex);
                
                // Save the table to the parameters
                m_params.SaveLutTable();
            }
        }

        #region Column headers renaming

        private void InitRenameTextBox()
        {
            m_tbColumnRename = new TextBox();
            m_tbColumnRename.MaxLength = 10;
            m_tbColumnRename.Leave += tbHeaderText_Leave;
        }

        private Point GetAbsoluteDgvHeaderCoordinate(Point location, int columnIndex)
        {
            int xCoord = 0; 
            for (int i = 0; i < columnIndex; i++)
            {
                if (m_dgvLutTable.Columns[i].Visible)
                    xCoord += m_dgvLutTable.Columns[i].Width;
            }
            return new Point(xCoord + location.X, location.Y);
        }

        private void CommitRenameColumnHeader()
        {
            // Get the column index from textbox Tag
            if (m_tbColumnRename.Tag == null)
                return;

            int columnIndex;
            if (Int32.TryParse(m_tbColumnRename.Tag.ToString(), out columnIndex) == false)
                return;

            // Change the header text
            m_dgvLutTable.Columns[columnIndex].HeaderText = m_tbColumnRename.Text;
            // Hide the textbox
            m_dgvLutTable.Controls.Remove(m_tbColumnRename);

            // Save value in the parameter
            if ((columnIndex >= INPUT_COLUMNS_START) && (columnIndex <= INPUT_COLUMNS_END))
            {
                m_params.SetInName(INPUT_COLUMNS_END - columnIndex, m_tbColumnRename.Text);
            }
            else if ((columnIndex >= OUTPUT_COLUMNS_START) && (columnIndex <= OUTPUT_COLUMNS_END))
            {
                m_params.SetOutName(OUTPUT_COLUMNS_END - columnIndex, m_tbColumnRename.Text);
            }
        }

        private void m_dgvLutTable_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Right) > 0)
            {
                if ((e.ColumnIndex >= INPUT_COLUMNS_START && e.ColumnIndex <= INPUT_COLUMNS_END) ||
                    (e.ColumnIndex >= OUTPUT_COLUMNS_START && e.ColumnIndex <= OUTPUT_COLUMNS_END))
                {
                    m_clickedColumnIndex = e.ColumnIndex;
                    m_contextMenuStripDgv.Show(m_dgvLutTable, GetAbsoluteDgvHeaderCoordinate(e.Location, e.ColumnIndex));
                }
            }
        }

        private void renameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_tbColumnRename.Width = m_dgvLutTable.Columns[m_clickedColumnIndex].Width;
            m_tbColumnRename.Text = m_dgvLutTable.Columns[m_clickedColumnIndex].HeaderText;
            m_tbColumnRename.Tag = m_clickedColumnIndex; // Tag is used to store the column index

            // Find textBox location
            int xCoord = GetAbsoluteDgvHeaderCoordinate(new Point(0, 0), m_clickedColumnIndex).X + 2; // 2 is offset
            int yCoord = Math.Max(0, (m_dgvLutTable.ColumnHeadersHeight - m_tbColumnRename.Height) / 2); // middle of the cell
            m_tbColumnRename.Location = new Point(xCoord, yCoord);


            m_dgvLutTable.Controls.Add(m_tbColumnRename);
            m_tbColumnRename.Focus();
            m_tbColumnRename.SelectAll();
        }

        void tbHeaderText_Leave(object sender, EventArgs e)
        {
            CommitRenameColumnHeader();
        }
        #endregion Column headers renaming

        private void m_bRename_Click(object sender, EventArgs e)
        {
            const string IN_TERM_PREFIX = "in";
            const string OUT_TERM_PREFIX = "out";

            // Dictionary: key - default name, value - non-default name (if exists)
            Dictionary<string, string> terminalNames = new Dictionary<string, string>();
            for (int i = 0; i < m_params.NumInputs; i++)
            {
                terminalNames.Add(String.Format("{0}{1}", IN_TERM_PREFIX, i), m_params.GetInName(i));
            }
            for (int i = 0; i < m_params.NumOutputs; i++)
            {
                terminalNames.Add(String.Format("{0}{1}", OUT_TERM_PREFIX, i), m_params.GetOutName(i));
            }
            foreach (string key in terminalNames.Keys.ToList())
            {
                if (terminalNames[key] == key)
                    terminalNames[key] = "";
            }

            foreach (KeyValuePair<string, string> terminalName in terminalNames)
            {
                if (terminalName.Value == terminalName.Key)
                    terminalNames[terminalName.Key] = "";
            }

            // Launch Rename dialog
            using (CyRenameDialog dialog = new CyRenameDialog(terminalNames))
            {
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    // Save results
                    foreach (KeyValuePair<string, string> terminalName in terminalNames)
                    {
                        // If value is empty, init with a default name , otherwise use entered
                        string newName = String.IsNullOrEmpty(terminalName.Value)
                            ? terminalName.Key
                            : terminalName.Value;

                        // Save separately 'in' and 'out' terminal names
                        if (terminalName.Key.StartsWith(IN_TERM_PREFIX))
                        {
                            int termIndex = Convert.ToInt32(terminalName.Key.Substring(IN_TERM_PREFIX.Length));
                            m_params.SetInName(termIndex, newName);
                            m_dgvLutTable.Columns[INPUT_COLUMNS_END - termIndex].HeaderText = newName;
                        }
                        else
                        {
                            int termIndex = Convert.ToInt32(terminalName.Key.Substring(OUT_TERM_PREFIX.Length));
                            m_params.SetOutName(termIndex, newName);
                            m_dgvLutTable.Columns[OUTPUT_COLUMNS_END - termIndex].HeaderText = newName;
                        }
                    }
                }
            }
        }
        #endregion Event handlers
    }

    internal class CyLutTable
    {
        public const int MAX_INPUTS = 5;
        public const int MAX_OUTPUTS = 8;
        public const int MAX_ROW_COUNT = (1 << MAX_INPUTS);
        private const int BITS_IN_BYTE = 8;

        public int InputCount { get; set; }
        public int OutputCount { get; set; }
        public List<CyLutTableRow> Rows { get; set; }

        /// <summary>
        ///  The number of rows that corresponds the number of inputs
        /// </summary>
        public int ActualRowCount
        {
            get { return (1 << InputCount); }
        }

        private CyLutTable()
        {
            Rows = new List<CyLutTableRow>();
            for (byte i = 0; i < MAX_ROW_COUNT; i++)
            {
                Rows.Add(new CyLutTableRow(this, i)); 
            }
        }

        public CyLutTable(int inputCount, int outputCount, string outputStr)
            : this()
        {
            InputCount = inputCount;
            OutputCount = outputCount;
            SetOutputFromString(outputStr);
        }

        /// <summary>
        /// Is called when the user changes the number of inputs
        /// </summary>
        /// <param name="inputCount">New number of inputs</param>
        public void ChangeInputCount(int inputCount)
        {
            int prevInputCount = InputCount;
            int prevActualRowCount = ActualRowCount;
            InputCount = inputCount;

            if (prevInputCount < InputCount)
            {
                int rowIndex = prevActualRowCount;
                // Initialize the output value with the same values as in the existed rows 
                while (rowIndex + prevActualRowCount <= ActualRowCount)
                {
                    for (int j = 0; j < prevActualRowCount; j++)
                    {
                        Rows[rowIndex++].SetOutputBitsFromOutput(Rows[j].Output);
                    }
                }
            }

            // Set to zero the rest rows output value
            for (int i = ActualRowCount; i < Rows.Count; i++)
            {
                Rows[i].SetOutputBitsFromOutput(0);
            }
        }

        /// <summary>
        /// Is called when the user changes the number of outputs
        /// </summary>
        /// <param name="inputCount">New number of outputs</param>
        public void ChangeOutputCount(int outputCount)
        {
            OutputCount = outputCount;

            // Set non-used bits to zero 
            for (int i = 0; i < Rows.Count; i++)
                for (int j = OutputCount; j < MAX_OUTPUTS; j++)
                {
                    Rows[i].OutputBits[j] = 0;
                }
        }

        /// <summary>
        /// Clear all output bits
        /// </summary>
        public void ClearOutput()
        {
            for (int i = 0; i < Rows.Count; i++)
                for (int j = 0; j < Rows[i].OutputBits.Length; j++)
                {
                    Rows[i].OutputBits[j] = 0;
                }
        }

        /// <summary>
        /// Set all output bits
        /// </summary>
        public void SetOutput()
        {
            for (int i = 0; i < Rows.Count; i++)
                for (int j = 0; j < OutputCount; j++)
                {
                    Rows[i].OutputBits[j] = 1;
                }
        }

        /// <summary>
        /// The maximum possible output value for a given munber of outputs
        /// </summary>
        /// <returns></returns>
        public byte GetMaxRowOutputValue()
        {
            return (byte)(1 << OutputCount);
        }

        /// <summary>
        /// Returns the output value in the format as it's stored in the symbol parameter, e.g. "FF221100"
        /// </summary>
        public string GetOutputString()
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < ActualRowCount; i++)
            {
                for (int j = OutputCount - 1; j >= 0; j--)
                {
                    sb.Append(Rows[i].OutputBits[j].ToString());
                }
            }
            string binaryValueStr = sb.ToString();
            sb.Clear();
            while (binaryValueStr.Length > 0)
            {
                int startIndex = Math.Max(0, binaryValueStr.Length - BITS_IN_BYTE);
                string byteStr = binaryValueStr.Substring(startIndex);
                string hexStr = CyUtils.ToHexStrNoPrefix(Convert.ToByte(byteStr, 2));
                sb.Insert(0, hexStr);

                binaryValueStr = binaryValueStr.Substring(0, startIndex);
            }

            return sb.ToString();
        }

        /// <summary>
        /// Initializes output values based on the string value from the symbol parameter.
        /// </summary>
        private void SetOutputFromString(string outputStr)
        {
            // Check if the string is in hex format
            if (String.IsNullOrEmpty(outputStr) || (CyUtils.ContainsOnlyHexChars(outputStr) == false))
            {
                Debug.Fail("SetOutputFromString(): Wrong format of outputStr");
                return;
            }
            // Add leading zero if the digit number is not even
            if (outputStr.Length % 2 != 0)
            {
                outputStr = "0" + outputStr;
            }

            int count = outputStr.Length / 2;
            StringBuilder sbBinaryOutput = new StringBuilder();
            for (int i = 0; i < count; i++)
            {
                // Divide the string into separate elements, two chars in each, starting from the end
                string itemStr = outputStr.Substring(i*2, 2);
                byte itemValue;
                CyUtils.ConvertHexStrToByte(itemStr, out itemValue);
                string binaryValueStr = Convert.ToString(itemValue, 2).PadLeft(BITS_IN_BYTE, '0');
                sbBinaryOutput.Append(binaryValueStr);
            }

            int totalBitsCount = ActualRowCount * OutputCount;
            if (sbBinaryOutput.Length > totalBitsCount)
            {
                sbBinaryOutput.Remove(0, sbBinaryOutput.Length - totalBitsCount);
            }
            else if (sbBinaryOutput.Length < totalBitsCount)
            {
                sbBinaryOutput.Insert(0, "".PadLeft(totalBitsCount - sbBinaryOutput.Length, '0'));
            }
            string binaryOutputStr = sbBinaryOutput.ToString();
            int binaryOutputStrIndex = 0;

            // Pass output values to the rows
            for (int i = 0; i < ActualRowCount; i++)
            {     
                for (int j = 0; j < OutputCount; j++)
                {
                    Rows[i].OutputBits[OutputCount - j - 1] =
                        Convert.ToByte(binaryOutputStr[binaryOutputStrIndex++].ToString());
                }
                for (int j = OutputCount; j < MAX_OUTPUTS; j++)
                {
                    Rows[i].OutputBits[j] = 0;
                }
            }
        }
    }

    internal class CyLutTableRow
    {
        private readonly CyLutTable m_parentTable;
        public byte InputValue { get; private set; }
        public byte[] OutputBits { get; set; }
       
        /// <summary>
        /// The output byte value
        /// </summary>
        public byte Output 
        {
            get
            {
                byte result = 0;
                for (int i = 0; i < m_parentTable.OutputCount; i++)
                {
                    result += (byte)(OutputBits[i] << i);
                }
                return result;
            }
        }

        /// <summary>
        /// The output value in hex format
        /// </summary>
        public string OutputStr
        {
            get { return CyUtils.ToHexStr(Output); }
        }

        public CyLutTableRow(CyLutTable parentTable, byte inputValue)
        {
            m_parentTable = parentTable;
            InputValue = inputValue;
            OutputBits = new byte[CyLutTable.MAX_OUTPUTS];
        }

        /// <summary>
        /// Fills the output bits array based on the output byte value
        /// </summary>
        public void SetOutputBitsFromOutput(byte output)
        {
            for (int i = 0; i < CyLutTable.MAX_OUTPUTS; i++)
            {
                OutputBits[i] = (output & (1 << i)) > 0 ? (byte)1 : (byte)0;
            }
        }

        /// <summary>
        /// Returns the list of bits which correspond the row index (InputValue)
        /// </summary>
        public List<byte> GetInputBitsValues()
        {
            List<byte> bits = new List<byte>();
            for (int i = 0; i < CyLutTable.MAX_INPUTS; i++)
            {
                bits.Add((InputValue & (1 << i)) > 0 ? (byte)1 : (byte)0);
            }
            return bits;
        }

        /// <summary>
        /// Changes the output bit value to the opposite (0/1)
        /// </summary>
        /// <param name="bitIndex"></param>
        public void InvertOutputBit(int bitIndex)
        {
            if (bitIndex < 0 || bitIndex >= OutputBits.Length)
            {
                Debug.Fail("InvertOutputBit(): Incorrect index");
                return;
            }

            OutputBits[bitIndex] = (byte)(1 - OutputBits[bitIndex]);
        }
    }
}
