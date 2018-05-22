/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace TCPWM_P4_v2_10
{
    /// <summary>
    /// |This class represents a control for editing Period and Compare registers settings on Timer/Counter and PWM tabs
    /// </summary>
    public partial class CyRegisterGrid : UserControl
    {
        #region Fields
        public CyParameters m_prms;

        private DataGridViewCell m_period1Cell;
        private DataGridViewCell m_period2Cell;
        private DataGridViewCell m_compare1Cell;
        private DataGridViewCell m_compare2Cell;
        private DataGridViewCheckBoxCell m_swapPeriodCell;
        private DataGridViewCheckBoxCell m_swapCompareCell;
        #endregion Fields

        public event EventHandler DataChanged;

        #region Constructor(s)
        public CyRegisterGrid()
        {
            InitializeComponent();
            InitDgvRegisters();
        }
        #endregion Constructor(s)

        #region Public functions
        public void UpdateVisibility()
        {
            if (m_prms == null) return;

            SetEnableCellStyle(m_period1Cell, IsCellEnable(m_period1Cell));
            SetEnableCellStyle(m_period2Cell, IsCellEnable(m_period2Cell));
            SetEnableCellStyle(m_swapPeriodCell, IsCellEnable(m_swapPeriodCell));

            SetEnableCellStyle(m_compare1Cell, IsCellEnable(m_compare1Cell));
            SetEnableCellStyle(m_compare2Cell, IsCellEnable(m_compare2Cell));
            SetEnableCellStyle(m_swapCompareCell, IsCellEnable(m_swapCompareCell));

            ValidatePeriodVsCompare();
        }

        public void UpdateFromParams()
        {
            m_period1Cell.Value = m_prms.Period1.ToString();
            if (m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL)
            {
                m_period2Cell.Value = m_prms.Period2.ToString();
                m_swapPeriodCell.Value = (m_prms.PeriodSwap == CyESwapEnable.SWAP_ENABLE);
            }
            else
            {
                m_swapPeriodCell.Value = false;
                m_period2Cell.Value = null;
            }

            m_compare1Cell.Value = m_prms.Compare1.ToString();
            m_compare2Cell.Value = m_prms.Compare2.ToString();
            m_swapCompareCell.Value = (m_prms.CompareSwap == CyESwapEnable.SWAP_ENABLE);

            UpdateVisibility();
        }

        public void ValidatePeriodVsCompare()
        {
            if (m_prms == null) return;
            // Check if Compare 1 value is less or equal than Period 1 value
            if ((m_prms.Compare1 > m_prms.Period1) &&
                IsCellEnable(m_compare1Cell) && IsCellEnable(m_period1Cell))
            {
                m_compare1Cell.ErrorText = Resources.CompareValueError;
            }
            else
            {
                m_compare1Cell.ErrorText = "";
            }

            // Check if Compare 2 value is less or equal than Period 2 value (when applicable)
            if (IsCellEnable(m_compare2Cell) && IsCellEnable(m_period2Cell) &&
                (m_prms.Compare2 > m_prms.Period2))
            {
                m_compare2Cell.ErrorText = Resources.CompareValueError;
            }
            else if (IsCellEnable(m_compare2Cell) && (IsCellEnable(m_period2Cell) == false) &&
                     IsCellEnable(m_period1Cell) && (m_prms.Compare2 > m_prms.Period1))
            {
                m_compare2Cell.ErrorText = Resources.CompareValueError;
            }
            else
            {
                m_compare2Cell.ErrorText = "";
            }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            for (int i = 0; i < dgvRegisters.ColumnCount; i++)
                for (int j = 0; j < dgvRegisters.RowCount; j++)
                {
                    string errText = dgvRegisters[i, j].ErrorText;
                    if ((String.IsNullOrEmpty(errText) == false) && (errText != Resources.CompareValueError))
                    {
                        string parameter = dgvRegisters[0, j].Value.ToString();
                        errs.Add(new CyCustErr(String.Format("{0}: {1}", parameter, errText)));
                    }
                }
            return errs;
        }
        #endregion Public functions

        #region Private functions
        private void InitDgvRegisters()
        {
            dgvRegisters.Rows.Clear();
            dgvRegisters.Rows.Add("Period", 0, true, 0);
            dgvRegisters.Rows.Add("Compare", 0, true, 0);
            this.Height = dgvRegisters.Rows[dgvRegisters.RowCount - 1].Height * 3 + 2;

            m_period1Cell = dgvRegisters[ColRegister1.Index, 0];
            m_period2Cell = dgvRegisters[ColRegister2.Index, 0];
            m_compare1Cell = dgvRegisters[ColRegister1.Index, 1];
            m_compare2Cell = dgvRegisters[ColRegister2.Index, 1];
            m_swapPeriodCell = (DataGridViewCheckBoxCell)dgvRegisters[ColSwap.Index, 0];
            m_swapCompareCell = (DataGridViewCheckBoxCell)dgvRegisters[ColSwap.Index, 1];

            dgvRegisters.CurrentCellDirtyStateChanged += dgvRegisters_CurrentCellDirtyStateChanged;
            dgvRegisters.CellPainting += dgvRegisters_CellPainting;
        }

       
        private void OnDataChanged()
        {
            if (DataChanged != null)
            {
                DataChanged(this, EventArgs.Empty);
            }
        }
            
        private string ValidateCellValue(string cellText)
        {
            int value = 0;
            string message = string.Format(Resources.RangeError, CyParameters.COMPARE_RANGE[0],
                CyParameters.COMPARE_RANGE[1]);
            bool isHex = CyParameters.IsHex(cellText);

            if (int.TryParse(cellText, out value) || isHex)
            {
                if (isHex) value = CyParameters.HexToInt(cellText);
                if (value >= CyParameters.COMPARE_RANGE[0] && value <= CyParameters.COMPARE_RANGE[1])
                {
                    message = "";
                }
            }
            return message;
        }
               
        private void SaveCheckBoxValueToParams(DataGridViewCheckBoxCell cell)
        {
            CyESwapEnable value = Convert.ToBoolean(cell.Value) ? CyESwapEnable.SWAP_ENABLE : 
                CyESwapEnable.SWAP_DISABLE;
            if (cell == m_swapPeriodCell)
            {
                m_prms.PeriodSwap = value;
            }
            else if (cell == m_swapCompareCell)
            {
                m_prms.CompareSwap = value;
            }
        }

        private void SaveTextBoxValueToParams(DataGridViewTextBoxCell cell)
        {
            UInt16 value = 0;
            bool isHex = CyParameters.IsHex(cell.Value.ToString());

            if (isHex)
                value = (UInt16)CyParameters.HexToInt(cell.Value.ToString());
            else
                value = UInt16.Parse(cell.Value.ToString());

            if (cell == m_period1Cell)
            {
                m_prms.Period1 = value;
            }
            else if (cell == m_period2Cell)
            {
                m_prms.Period2 = value;
            }
            else if (cell == m_compare1Cell)
            {
                m_prms.Compare1 = value;
            }
            else if (cell == m_compare2Cell)
            {
                m_prms.Compare2 = value;
            }
        }
       
        private bool IsCellEnable(DataGridViewCell cell)
        {
            bool isEnable = true;
            if (cell == m_period1Cell)
            {
                isEnable = true;
            }
            else if (cell == m_period2Cell)
            {
                isEnable = (m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL) && 
                           (m_prms.PeriodSwap == CyESwapEnable.SWAP_ENABLE);
            }
            else if (cell == m_swapPeriodCell)
            {
                isEnable = (m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL); 
            }
            else if (cell == m_compare1Cell)
            {
                isEnable = (m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL) ||
                           (m_prms.CompCapMode == CyECompCapMode.Compare);
            }
            else if (cell == m_compare2Cell)
            {
                isEnable = ((m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL) ||
                           (m_prms.CompCapMode == CyECompCapMode.Compare)) &&
                           (m_prms.CompareSwap == CyESwapEnable.SWAP_ENABLE);
            }
            else if (cell == m_swapCompareCell)
            {
                isEnable = (m_prms.TCPWMConfig == CyETCPWMConfig.PWM_SEL) ||
                           (m_prms.CompCapMode == CyECompCapMode.Compare);
            }
            return isEnable;
        }

        private void SetEnableCellStyle(DataGridViewCell cell, bool isEnabled)
        {
            DataGridViewCellStyle disabledStyle = new DataGridViewCellStyle();
            disabledStyle.BackColor = SystemColors.Control;
            disabledStyle.SelectionBackColor = disabledStyle.BackColor;
            disabledStyle.SelectionForeColor = dgvRegisters.DefaultCellStyle.ForeColor;
            if (isEnabled)
            {
                cell.ReadOnly = false;
                if (cell is DataGridViewCheckBoxCell)
                    cell.Style = ColSwap.DefaultCellStyle;
                else
                    cell.Style = ColRegister1.DefaultCellStyle;
            }
            else
            {
                cell.ReadOnly = true;
                cell.Style = disabledStyle;
            }
        }
        #endregion Private functions

        #region Event handlers
        void dgvRegisters_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            if (dgvRegisters.IsCurrentCellDirty)
            {
                dgvRegisters.CommitEdit(DataGridViewDataErrorContexts.Commit);
            }
        }

        private void dgvRegisters_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if ((e.ColumnIndex < 0) || (e.RowIndex < 0) || (e.ColumnIndex == ColHeader.Index))
                return;

            DataGridViewCell cell = dgvRegisters[e.ColumnIndex, e.RowIndex];
            string errText = "";

            if (IsCellEnable(cell) == false)
                return;

            if (e.ColumnIndex == ColRegister1.Index || e.ColumnIndex == ColRegister2.Index)
            {
                string celText = (cell.Value != null) ? cell.Value.ToString() : "";

                errText = ValidateCellValue(celText);
                if (String.IsNullOrEmpty(errText) == false)
                {
                    dgvRegisters[e.ColumnIndex, e.RowIndex].ErrorText = errText;
                }
                else
                {
                    dgvRegisters[e.ColumnIndex, e.RowIndex].ErrorText = "";
                }
            }

            if (cell.Value == null)
                return;

            if (String.IsNullOrEmpty(errText) == false)
                return;

            if (e.ColumnIndex == ColSwap.Index)
            {
                SaveCheckBoxValueToParams((DataGridViewCheckBoxCell)cell);
            }
            else
            {
                SaveTextBoxValueToParams((DataGridViewTextBoxCell)cell);
            }

            UpdateVisibility();
            OnDataChanged();
        }

        void dgvRegisters_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            if ((e.ColumnIndex == ColSwap.Index) && (e.RowIndex == 0) &&
                (m_prms != null) && (m_prms.TCPWMConfig == CyETCPWMConfig.TIMER))
            {
                e.Paint(e.ClipBounds, DataGridViewPaintParts.Border | DataGridViewPaintParts.Background);
                e.Handled = true;
            }
        }
        #endregion Event handlers
    }
}
