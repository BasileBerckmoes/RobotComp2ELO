/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;

namespace TrimMargin_v3_0.Controls
{
    internal class CyColumnVisibilityCheckedListBox : CheckedListBox
    {
        #region Members
        private DataGridView m_dgv;
        private List<DataGridViewColumn> m_grayOutColumns;
        private bool m_initializing = false;

        private Dictionary<int, int> m_checkboxIndexToColIndex;
        #endregion Members

        private DataGridViewColumn GetColumn(int itemIndex)
        {
            return m_dgv.Columns[m_checkboxIndexToColIndex[itemIndex]];
        }

        public CyColumnVisibilityCheckedListBox(DataGridView dgv, List<DataGridViewColumn> notIncludedColumns,
            List<DataGridViewColumn> grayOutColumns)
        {
            this.CheckOnClick = true;
            this.IntegralHeight = false;

            m_dgv = dgv;
            m_grayOutColumns = grayOutColumns;

            m_checkboxIndexToColIndex = new Dictionary<int, int>();

            m_initializing = true;
            foreach (DataGridViewColumn col in m_dgv.Columns)
            {
                if (notIncludedColumns.Contains(col))
                    continue;

                int index;
                if (!col.Visible)
                {
                    index = this.Items.Add(col.HeaderText, CheckState.Unchecked);
                }
                else if (m_grayOutColumns.Contains(col))
                {
                    index = this.Items.Add(col.HeaderText, CheckState.Indeterminate);
                }
                else
                {
                    index = this.Items.Add(col.HeaderText, CheckState.Checked);
                }
                m_checkboxIndexToColIndex.Add(index, col.Index);
            }
            m_initializing = false;
        }

        #region Events

        protected override void OnItemCheck(ItemCheckEventArgs e)
        {
            if (!m_initializing)
            {
                DataGridViewColumn col = GetColumn(e.Index);

                switch (e.CurrentValue)
                {
                    case CheckState.Indeterminate:
                        if (e.NewValue != CheckState.Indeterminate)
                        {
                            //abort the state change, column remains visible
                            e.NewValue = CheckState.Indeterminate;
                            OnItemCheck(e);
                        }
                        break;

                    case CheckState.Checked:
                    case CheckState.Unchecked:
                        col.Visible = (e.NewValue == CheckState.Checked);
                        break;
                }
            }

            base.OnItemCheck(e);
        }

        protected override void OnDrawItem(DrawItemEventArgs e)
        {
            DrawItemEventArgs args;
            DataGridViewColumn col = GetColumn(e.Index);

            if (m_grayOutColumns.Contains(col))
            {
                args = new DrawItemEventArgs(e.Graphics, e.Font, e.Bounds,
                    e.Index, e.State, SystemColors.GrayText, e.BackColor);
            }
            else
            {
                args = e;
            }

            base.OnDrawItem(args);
        }

        #endregion Events
    }
}