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

namespace CyCustomizer.CyStatusReg_v1_90
{
    public partial class CyBitfieldControl : UserControl
    {
        public const int MIN_INPUTS = 1;
        public const int MAX_INPUTS = 8;
        public const int DEFAULT_MASKVALUE = 0;
        public const int FIRST_CELL = 0;
        public const int SECOND_CELL = 1;
        public const int THIRD_CELL = 2;
        public const int MIN_ROW_INDEX = 0;
        public const int MAX_ROW_INDEX = 7;
        public const int DGV_THIRD_COL = 2;

        public static int maskval;

        public ICyInstEdit_v1 m_Component = null;

        public CyBitfieldControl(ICyInstEdit_v1 inst)
        {
            m_Component = inst;
            InitializeComponent();

            m_dgvBitFieldConfig.Rows.Add(MAX_INPUTS);

            cbSetAll.SelectedIndex = 0;
        }

        private void CyBitfieldControl_Load(object sender, EventArgs e)
        {
            UpdateFormFromParams(m_Component);
        }

        private void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            bool busValue = false;
            bool intValue = false;
            int inputs = GetNumInputs();

            int.TryParse(m_Component.GetCommittedParam(CyStatusReg_v1_90.StatusRegParameters.MASKVALUE).Value,
                            out maskval);

            // Set bit modes and mask value columns
            SetColumns_BitMode_MaskValue();

            // Set Display as Bus check box
            bool.TryParse(m_Component.GetCommittedParam(CyStatusReg_v1_90.StatusRegParameters.BUS).Value, out busValue);
            chBus.Checked = busValue;

            // Set Generate Interrupt check box
            bool.TryParse(m_Component.GetCommittedParam(CyStatusReg_v1_90.StatusRegParameters.INTRR).Value,
                            out intValue);
            chInterrupt.Checked = intValue;

            // Set value for Inputs
            nInputs.Value = inputs;

            // Enables NumInputs Rows
            SetBitsVisibility(inst);
        }

        private int GetNumInputs()
        {
            int inputs;

            if (!Int32.TryParse(m_Component.GetCommittedParam(CyStatusReg_v1_90.StatusRegParameters.NUMINPUTS).Value,
                out inputs))
            {
                // Minimum number of inputs
                inputs = MIN_INPUTS;
            }

            // Limit the inputs parameter
            return (inputs >= MAX_INPUTS ? MAX_INPUTS :
                    inputs < MIN_INPUTS ? MIN_INPUTS :
                    inputs);
        }

        private void SetBitsVisibility(ICyInstEdit_v1 inst)
        {
            int inputs = GetNumInputs();

            // Set Bits visibility depending on number of inputs value
            for (int i = 0; i < inputs; i++)
            {
                m_dgvBitFieldConfig.Rows[i].Visible = true;
            }

            for (int i = inputs; i < MAX_INPUTS; i++)
            {
                m_dgvBitFieldConfig.Rows[i].Visible = false;
            }

            // Handles the Interrupt mask column visibility
            if (!(chInterrupt.Checked))
            {
                m_dgvBitFieldConfig.Columns[DGV_THIRD_COL].Visible = false;
            }
            else
            {
                m_dgvBitFieldConfig.Columns[DGV_THIRD_COL].Visible = true;
            }
            SetDgvSize();
        }

        // Load values to the DataGridView rows
        private void SetColumns_BitMode_MaskValue()
        {
            short bitMode = 0;
            int mask_val = 0;
            mask_val = maskval;

            for (int i = MIN_ROW_INDEX; i <= MAX_ROW_INDEX; i++)
            {
                DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                row.Cells[FIRST_CELL].Value = i;

                Int16.TryParse(m_Component.GetCommittedParam(Resource.BIT + i + Resource.MODE).Value, out bitMode);
                row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[bitMode];

                if(i != MAX_INPUTS - 1)
                {
                    row.Cells[THIRD_CELL].Value = 
                    ((DataGridViewComboBoxCell)row.Cells[THIRD_CELL]).Items[Convert.ToInt16((int)mask_val & 0x01)];
                    mask_val = mask_val >> 1;
                }
            }

            SetDgvSize();
            m_dgvBitFieldConfig.CurrentCell = m_dgvBitFieldConfig[MIN_ROW_INDEX, FIRST_CELL];
            m_dgvBitFieldConfig.ClearSelection();
        }

        private void CheckAndSaveAllParams()
        {
            errIntr.SetError(chInterrupt, "");

            if (errCheck())    // Generate error
            {
                errIntr.SetError(chInterrupt, Resource.InterruptErrMsg);
            }
            else    // No error is reported, save all the parameters to symbol
            {
                // Save NumInputs parameter
                m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.NUMINPUTS, nInputs.Value.ToString());
                m_Component.CommitParamExprs();
                
                // Save Bus parameter
                if (chBus.Checked)
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.BUS, Resource.TRUE);
                }
                else
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.BUS, Resource.FALSE);
                }

                // Save BitMode values
                for (int i = 0; i < MAX_INPUTS; i++)
                {
                    DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                    if ((string)row.Cells[SECOND_CELL].Value == Resource.TRANSPARENT)
                    {
                        m_Component.SetParamExpr(Resource.BIT + i + Resource.MODE, Resource.TRANSPARENT);
                    }
                    else
                    {
                        m_Component.SetParamExpr(Resource.BIT + i + Resource.MODE, Resource.STICKY);
                    }
                }

                // Save interrupt and mask values
                if (chInterrupt.Checked)
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.INTRR, Resource.TRUE);
                }
                else
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.INTRR, Resource.FALSE);
                }
                SetMaskValue();

                m_Component.CommitParamExprs();
                SetBitsVisibility(m_Component);
            }
        }

        private void nInputs_ValueChanged(object sender, EventArgs e)
        {
            CheckAndSaveAllParams();
        }

        public void UpdateFormFromInst(ICyInstEdit_v1 inst)
        {
           UpdateFormFromParams(inst);
        }

        private void nInputs_KeyUp(object sender, KeyEventArgs e)
        {
            CheckAndSaveAllParams();
        }

        // Saves the BUS parameter
        private void chBus_CheckedChanged(object sender, EventArgs e)
        {
            if (!errCheck())
            {
                if (chBus.Checked == true)
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.BUS, Resource.TRUE);
                }
                else
                {
                    m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.BUS, Resource.FALSE);
                }
                m_Component.CommitParamExprs();
            }
        }

        private void bSetAll_Click(object sender, EventArgs e)
        {
            int inputs = GetNumInputs();

            short index = (short)cbSetAll.SelectedIndex;

            for (int i = 0; i < inputs; i++)
            {
                DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                row.Cells[SECOND_CELL].Value = ((DataGridViewComboBoxCell)row.Cells[SECOND_CELL]).Items[index];
            }

            if (!errCheck())
            {
                if (index == 0)    // Set the bit modes to Transparent
                {
                    for (int i = 0; i < inputs; i++)
                    {
                        m_Component.SetParamExpr(Resource.BIT + i + Resource.MODE, Resource.TRANSPARENT);
                        m_Component.CommitParamExprs();
                    }
                }
                else    // Set the bit modes to Sticky
                {
                    for (int i = 0; i < inputs; i++)
                    {
                        m_Component.SetParamExpr(Resource.BIT + i + Resource.MODE, Resource.STICKY);
                        m_Component.CommitParamExprs();
                    }
                }
            }
        }

        private void chInterrupt_CheckedChanged(object sender, EventArgs e)
        {
            CheckAndSaveAllParams();
        }

        // Save the changed Bit mode and Interrupt mask value
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

            if (!errCheck())
            {
                int rowIndex = m_dgvBitFieldConfig.CurrentCell.RowIndex;
                int colIndex = m_dgvBitFieldConfig.CurrentCell.ColumnIndex;

                if ((cb != null) && (colIndex != THIRD_CELL))    // Save the Bit mode
                {
                    if (cb.SelectedIndex == 0)
                    {
                        m_Component.SetParamExpr(Resource.BIT + rowIndex + Resource.MODE, Resource.TRANSPARENT);
                    }
                    else
                    {
                        m_Component.SetParamExpr(Resource.BIT + rowIndex + Resource.MODE, Resource.STICKY);
                    }
                    m_Component.CommitParamExprs();
                }
                else if ((cb != null) && (colIndex != SECOND_CELL))    // Save the Interrupt mask
                {
                    SetMaskValue();
                }
            }
        }

        private void m_dgvBitFieldConfig_Enter(object sender, EventArgs e)
        {
            m_dgvBitFieldConfig.CurrentCell = m_dgvBitFieldConfig[MIN_ROW_INDEX, FIRST_CELL];
            m_dgvBitFieldConfig.ClearSelection();
        }

        // Saves mask value
        private void SetMaskValue()
        {
            int val = 0;
            maskval = DEFAULT_MASKVALUE;

            for (int i = 0; i < (MAX_INPUTS - 1); i++)
            {
                DataGridViewRow row = m_dgvBitFieldConfig.Rows[i];
                val = Convert.ToInt16(row.Cells[THIRD_CELL].EditedFormattedValue);
                val = val << i;
                maskval = maskval | val;
            }

            m_Component.SetParamExpr(CyStatusReg_v1_90.StatusRegParameters.MASKVALUE, maskval.ToString());
            m_Component.CommitParamExprs();
        }

        // Returns true if error exists
        private bool errCheck()
        {
            return ((chInterrupt.Checked == true && nInputs.Value == MAX_INPUTS) ? true : false);
        }

        #region m_dgvBitFieldConfig size
        int GetDgvMaxWidth()
        {
            int w = 0;
            foreach (DataGridViewColumn col in m_dgvBitFieldConfig.Columns)
            {
                w += col.Width + col.DividerWidth;
            }
            return w + 5;
        }
        private int GetDgvThirdColumnWidth()
        {
            return InterruptMask.Width;
        }
        private int GetDgvRowHeight()
        {
            return m_dgvBitFieldConfig.RowTemplate.Height;
        }
        private int GetDgvMaxHeight()
        {
            return m_dgvBitFieldConfig.ColumnHeadersHeight + (GetDgvRowHeight() * MAX_INPUTS) + 3;
        }
        private void SetDgvSize()
        {
            if (!(chInterrupt.Checked))
            {
                m_dgvBitFieldConfig.Width = GetDgvMaxWidth() - GetDgvThirdColumnWidth();
            }
            else
            {
                m_dgvBitFieldConfig.Width = GetDgvMaxWidth();
            }

            m_dgvBitFieldConfig.Height = GetDgvMaxHeight() - (GetDgvRowHeight() * (MAX_INPUTS - GetNumInputs()));
        }
        #endregion m_dgvBitFieldConfig size
    }
}
