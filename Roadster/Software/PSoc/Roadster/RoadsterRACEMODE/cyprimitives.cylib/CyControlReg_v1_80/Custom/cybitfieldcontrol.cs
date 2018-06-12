/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Text.RegularExpressions;
using CyDesigner.Extensions.Gde;

namespace CyCustomizer.CyControlReg_v1_80
{
    public partial class CyBitfieldControl : UserControl
    {
        public const int DEFAULT_OUTPUT = 1;
        public const int NUMOUTPUT_MAX = 8;
        public const int DEFAULT_BITVALUE = 0;
        public const int FIRST_CELL = 0;
        public const int SECOND_CELL = 1;
        public const int THIRD_CELL = 2;
        public const int MIN_ROW_INDEX = 0;
        public const int MAX_ROW_INDEX = 7;

        public static int bit_all;
        public static int bitval;

        public ICyInstEdit_v1 m_Component = null;

        public CyBitfieldControl(ICyInstEdit_v1 inst)
        {
            m_Component = inst;
            InitializeComponent();

            m_dgvBitFieldConfig.Rows.Add(NUMOUTPUT_MAX);
            cbSetAll.SelectedIndex = 0;

            UpdateFormFromParams(inst);
        }

        private void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            short resetValue = 1;
            bool extResetValue = false;
            bool busValue = false;
            int bv;
            int val_one = 0xff;
            int outputs = GetNumOutputs();

            if (!Int32.TryParse(m_Component.GetCommittedParam(Resources.BITVALUE).Value, out bv)) { bv = 0; }

            if (bv != bitval)
            {
                if (bit_all == 0)
                {
                    bit_all = bv;
                }
                else
                {
                    bitval = bv;
                    val_one = val_one << outputs;
                    bit_all = bit_all & val_one;
                    bit_all = bit_all | bitval;
                }
            }

            // Sets Bit modes and Initial value columns
            SetColumns_BitMode_InitialValue();

            // Set value for Output
            nInputs.Value = outputs;

            // Set value of External reset check box
            bool.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.EXTERNALRESET).Value,
                            out extResetValue);
            chReset.Checked = extResetValue;

            Int16.TryParse(m_Component.GetCommittedParam("ResetCheck").Value, out resetValue);
            chReset.Enabled = resetValue == 0 ? true : false;

            // Set value of Display as Bus check box
            bool.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.BUS).Value,
                            out busValue);
            chBus.Checked = busValue;

            // Enables numberoutput rows.
            SetBitsVisibility(inst);
        }

        private int GetNumOutputs()
        {
            int outputs;

            if (!Int32.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS).Value,
                out outputs))
            {
                // Minimum number of output
                outputs = DEFAULT_OUTPUT;
            }

            // Limit the numberoutput parameter , wrong value may come from older version of Control Register
            return (outputs >= NUMOUTPUT_MAX ? NUMOUTPUT_MAX :
                    outputs < DEFAULT_OUTPUT ? DEFAULT_OUTPUT :
                    outputs);
        }

        private void SetBitsVisibility(ICyInstEdit_v1 inst)
        {
            int outputs = GetNumOutputs();

            // Set Bits visibility depending on number of outputs value
            for (int i = 0; i < outputs; i++)
            {
                m_dgvBitFieldConfig.Rows[i].Visible = true;
            }

            for (int i = outputs; i < NUMOUTPUT_MAX; i++)
            {
                m_dgvBitFieldConfig.Rows[i].Visible = false;
            }

            SetDgvSize();
        }

        // Load values to the DataGridView rows
        private void SetColumns_BitMode_InitialValue()
        {
            short bitValue = 0;
            int val = bit_all;

            for (int i = MIN_ROW_INDEX; i <= MAX_ROW_INDEX; i++)
            {
                DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];

                row.Cells[FIRST_CELL].Value = i;

                Int16.TryParse(m_Component.GetCommittedParam(Resources.BIT + i.ToString() + Resources.MODE).Value,
                        out bitValue);

                if (bitValue == 3) { bitValue = 2; }

                row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[bitValue];
                row.Cells[THIRD_CELL].Value = 
                ((DataGridViewComboBoxCell)row.Cells[THIRD_CELL]).Items[Convert.ToInt16(((int)val & 0x01))];
                val = val >> 1;
            }

            SetDgvSize();
            m_dgvBitFieldConfig.CurrentCell = m_dgvBitFieldConfig[MIN_ROW_INDEX, FIRST_CELL];
            m_dgvBitFieldConfig.ClearSelection();
        }

        private void SaveOutputParameter()
        {
            // Saves the NUMOUTPUTS
            int outputs = GetNumOutputs();

            if (outputs != nInputs.Value)
            {
                m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS, nInputs.Value.ToString());
                m_Component.CommitParamExprs();

                ValidatingExternalReset();
                SetBitValue();

                SetBitsVisibility(m_Component);
            }
        }

        // Saves the OUTPUT value assigned to the control
        private void nInputs_ValueChanged(object sender, EventArgs e)
        {
            SaveOutputParameter();
        }

        public void UpdateFormFromInst(ICyInstEdit_v1 inst)
        {
            UpdateFormFromParams(inst);
        }

        // Handles keyboard events. Save OUTPUT value on Key release
        private void nInputs_KeyUp(object sender, KeyEventArgs e)
        {
            SaveOutputParameter();
        }

        // Check for the ExternalReset validity
        private void ValidatingExternalReset()
        {
            short resetValue;

            Int16.TryParse(m_Component.GetCommittedParam("ResetCheck").Value, out resetValue);
            chReset.Enabled = resetValue == 0 ? true : false;
        }

        private void chReset_Validating(object sender, CancelEventArgs e)
        {
            // Validates the external reset parameter
            ValidatingExternalReset();
        }

        private void chReset_CheckedChanged(object sender, EventArgs e)
        {
            // Saves the EXTERNALRESET parameter
            if (chReset.Checked == true)
            {
                m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.EXTERNALRESET, Resources.TRUE);
            }
            else
            {
                m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.EXTERNALRESET, Resources.FALSE);
            }
            m_Component.CommitParamExprs();
        }

        // Saves Bit value
        private void SetBitValue()
        {
            int val = 0;
            int val_one = 0xff;
            int outputs = GetNumOutputs();

            bitval = DEFAULT_BITVALUE;

            for (int i = 0; i < outputs; i++)
            {
                DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                val = Convert.ToInt16(row.Cells[THIRD_CELL].EditedFormattedValue);
                val = val << i;
                bitval = bitval | val;
            }

            val_one = val_one << outputs;
            bit_all = bit_all & val_one;
            bit_all = bit_all | bitval;

            m_Component.SetParamExpr(Resources.BITVALUE, bitval.ToString());
            m_Component.CommitParamExprs();
        }

        private void bSetAll_Click(object sender, EventArgs e)
        {
            int outputs = GetNumOutputs();
            short index = (short)cbSetAll.SelectedIndex;

            switch (index)
            {
                case 0:    // Set the bit modes to Direct
                    for (int i = 0; i < outputs; i++)
                    {
                        DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                        row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[index];
                        m_Component.SetParamExpr(Resources.BIT + i + Resources.MODE, Resources.DIRECTMODE);
                        m_Component.CommitParamExprs();
                    }
                    break;

                case 1:    // Set the bit modes to Sync
                    for (int i = 0; i < outputs; i++)
                    {
                        DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                        row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[index];
                        m_Component.SetParamExpr(Resources.BIT + i + Resources.MODE, Resources.SYNCMODE);
                        m_Component.CommitParamExprs();
                    }
                    break;

                case 2:    // Set the bit modes to Pulse
                    for (int i = 0; i < outputs; i++)
                    {
                        DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                        row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[index];
                        m_Component.SetParamExpr(Resources.BIT + i + Resources.MODE, Resources.PULSEMODE);
                        m_Component.CommitParamExprs();
                    }
                    break;
            }

            ValidatingExternalReset();
        }

        // Save the changed Bit mode and Bit value
        private void m_dgvBitFieldConfig_EditingControlShowing(object sender,
                        DataGridViewEditingControlShowingEventArgs e)
        {
            ComboBox cb = e.Control as ComboBox;

            if (cb != null)
            {
                // Remove the event handler to avoid attaching multiple
                cb.Enter -= new EventHandler(cb_Enter);
                cb.SelectedIndexChanged -= new EventHandler(cb_SelectedIndexChanged);

                // Attach the event handler
                cb.Enter += new EventHandler(cb_Enter);
                cb.SelectedIndexChanged += new EventHandler(cb_SelectedIndexChanged);

                // Fix the black background on the drop down menu
                e.CellStyle.BackColor = this.m_dgvBitFieldConfig.DefaultCellStyle.BackColor;
            }
            m_dgvBitFieldConfig.ClearSelection();
        }

        void cb_Enter(object sender, EventArgs e)
        {
            ComboBox cb = (ComboBox)sender;

            if ((cb != null))
            {
                // Display the dropdown on the first click
                cb.DroppedDown = true;
            }
        }

        void cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = (ComboBox)sender;
            int rowIndex = m_dgvBitFieldConfig.CurrentCell.RowIndex;
            int colIndex = m_dgvBitFieldConfig.CurrentCell.ColumnIndex;

            if ((cb != null) && (colIndex != THIRD_CELL))    // Save the Bit mode
            {
                switch (cb.SelectedIndex)
                {
                    case 0:
                        m_Component.SetParamExpr(Resources.BIT + (rowIndex) + Resources.MODE, Resources.DIRECTMODE);
                        break;

                    case 1:
                        m_Component.SetParamExpr(Resources.BIT + (rowIndex) + Resources.MODE, Resources.SYNCMODE);
                        break;

                    case 2:
                        m_Component.SetParamExpr(Resources.BIT + (rowIndex) + Resources.MODE, Resources.PULSEMODE);
                        break;
                }
                m_Component.CommitParamExprs();

                ValidatingExternalReset();
            }
            else if ((cb != null) && (colIndex != SECOND_CELL))    // Save the Bit value
            {
                SetBitValue();
            }
        }

        private void m_dgvBitFieldConfig_Enter(object sender, EventArgs e)
        {
            m_dgvBitFieldConfig.CurrentCell = m_dgvBitFieldConfig[MIN_ROW_INDEX, FIRST_CELL];
            m_dgvBitFieldConfig.ClearSelection();
        }

        private void chBus_CheckedChanged(object sender, EventArgs e)
        {
            // Saves the BUS parameter
            if (chBus.Checked == true)
            {
                m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BUS, Resources.TRUE);
            }
            else
            {
                m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BUS, Resources.FALSE);
            }
            m_Component.CommitParamExprs();
        }

        #region m_dgvBitFieldConfig size
        private int GetDgvRowHeight()
        {
            return m_dgvBitFieldConfig.RowTemplate.Height;
        }
        private int GetDgvMaxHeight()
        {
            return m_dgvBitFieldConfig.ColumnHeadersHeight + (GetDgvRowHeight() * NUMOUTPUT_MAX) + 3;
        }
        private void SetDgvSize()
        {
            m_dgvBitFieldConfig.Height = GetDgvMaxHeight() - (GetDgvRowHeight() * (NUMOUTPUT_MAX - GetNumOutputs()));
        }
        #endregion m_dgvBitFieldConfig size
    }
}
